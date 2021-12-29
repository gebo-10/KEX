#vert
#version 310 es
precision highp float;

layout(std140, binding = 0) uniform Common
{
	vec4 time;
	vec4 light_dir;
	vec4 light_color;
	mat4 V;
	mat4 P;
	mat4 PV;
};
layout (location = 0) uniform mat4 M;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 4) in vec2 uv;


out vec3 frag_position;
out vec3 normal_lerped;
out vec2 texture_coord;

void main()
{
	vec4 word_pos=M*vec4(position,1.0);
	gl_Position = PV*word_pos;
	frag_position=word_pos.xyz;

	vec4 world_normal=M*vec4(normal,1.0);
	normal_lerped = world_normal.xyz;
	texture_coord = uv;
}

//////////////////////////////////////////////////////////////////////////////
#frag
#version 310 es
precision highp float;


layout(std140, binding = 0) uniform Common
{
	vec4 time;
	vec4 light_dir;
	vec4 light_color;
	mat4 V;
	mat4 P;
	mat4 PV;
};
layout (location = 1) uniform vec4 c;
layout (binding = 1)  uniform sampler2D texture0;
in vec3 normal_lerped;
in vec3 frag_position;
in vec2 texture_coord;

layout(location = 0) out vec4 FragColor;

uniform vec3  albedo;     // value=1,0,0
uniform float metallic;   // value=0, min=0, max=1, step=0.001
uniform float roughness;  // value=0.2, min=0, max=1, step=0.001
uniform float ao;

const float PI = 3.14159265359;

float distributionGGX (vec3 N, vec3 H, float roughness){
    float a2    = roughness * roughness * roughness * roughness;
    float NdotH = max (dot (N, H), 0.0);
    float denom = (NdotH * NdotH * (a2 - 1.0) + 1.0);
    return a2 / (PI * denom * denom);
}

float geometrySchlickGGX (float NdotV, float roughness){
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;
    return NdotV / (NdotV * (1.0 - k) + k);
}

float geometrySmith (vec3 N, vec3 V, vec3 L, float roughness){
    return geometrySchlickGGX (max (dot (N, L), 0.0), roughness) * 
           geometrySchlickGGX (max (dot (N, V), 0.0), roughness);
}

vec3 fresnelSchlick (float cosTheta, vec3 F0){
    return F0 + (1.0 - F0) * pow (1.0 - cosTheta, 5.0);
}

void main()
{		
    vec3 N = normalize(Normal);
    vec3 V = normalize(camPos - WorldPos);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);
	           
    // reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < 4; ++i) 
    {
        // calculate per-light radiance
        vec3 L = normalize(lightPositions[i] - WorldPos);
        vec3 H = normalize(V + L);
        float distance    = length(lightPositions[i] - WorldPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = lightColors[i] * attenuation;        
        
        // cook-torrance brdf
        float NDF = DistributionGGX(N, H, roughness);        
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);       
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;	  
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular     = numerator / denominator;  
            
        // add to outgoing radiance Lo
        float NdotL = max(dot(N, L), 0.0);                
        Lo += (kD * albedo / PI + specular) * radiance * NdotL; 
    }   
  
    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;
	
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  
   
    FragColor = vec4(color, 1.0);
}  

//////////////////////////////////////////////////////////////////////////////
#decl
return{
	{
		name="M",
		location = 0,
		type=ShaderDataType.MAT4,
		value={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	},
	{
		name="c",
		location = 1,
		type=ShaderDataType.Color,
		value={0.9,0.5,0.1,1}--  ,0.2,0.9,0.3,1,  0.9,0.2,0.3,1}
	}
}
