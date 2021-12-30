#vert
#version 310 es
precision highp float;
struct Camera{
	vec4 clear_color;
	vec4 viewport;
	vec4 position;
	mat4 V;
	mat4 P;
	mat4 PV;
};
struct Light{
	ivec4 type;		//x=LightType
	vec4 position;  // 灯的位置 
	vec4 direction; // 方向光源
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 param; // 衰减常数 // 衰减一次系数// 衰减二次系数 // 聚光灯张角的余弦值
};
layout(std140, binding = 0) uniform Common
{
	vec4 time;
	Camera cameras[8];
	Light lights[16];
};

layout (location = 0) uniform mat4 M;
layout (location = 1) uniform int camera_id;

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
	Camera camera=cameras[camera_id];
	gl_Position = camera.PV*word_pos;
	frag_position=word_pos.xyz;


	vec4 world_normal=M*vec4(normal,1.0);
	normal_lerped = world_normal.xyz;
	texture_coord = uv;
}

//////////////////////////////////////////////////////////////////////////////
#frag
#version 310 es
precision highp float;

struct Camera{
	vec4 clear_color;
	vec4 viewport;
	vec4 position;
	mat4 V;
	mat4 P;
	mat4 PV;
};
struct Light{
	ivec4 type;		//x=LightType
	vec4 position;  // 灯的位置 
	vec4 direction; // 方向光源
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 param; // 衰减常数 // 衰减一次系数// 衰减二次系数 // 聚光灯张角的余弦值
};
layout(std140, binding = 0) uniform Common
{
	vec4 time;
	Camera cameras[8];
	Light lights[16];
};

layout (location = 0) uniform mat4 M;
layout (location = 1) uniform int camera_id;
layout (location = 2) uniform float shininess;
layout (binding = 1)  uniform sampler2D texture0;

in vec3 normal_lerped;
in vec3 frag_position;
in vec2 texture_coord;

layout(location = 0) out vec4 color;

vec3 CalcDirLight(Light light, vec3 normal)
{
    vec3 lightDir = -normalize(light.direction.xyz/light.direction.w);
	//vec3 lightDir = normalize(vec3(-1,-1,1));
    float diff = max(dot(normal, lightDir), 0.0);

    //vec3 reflectDir = reflect(-lightDir, normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    vec3 ambient  = light.ambient.xyz;
    vec3 diffuse  = light.diffuse.xyz  * diff ;
    //vec3 specular = light.specular.xyz * spec ;
    return ( ambient+diffuse );
}

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos)
{
	vec3 light_position=light.position.xyz;
	float constant=0.5;
	float quadratic=0.1;
	float linear=0.3;
    vec3 lightDir = normalize(light_position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    //vec3 reflectDir = reflect(-lightDir, normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light_position - fragPos);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient.xyz ;
    vec3 diffuse  = light.diffuse.xyz  * diff ;
    //vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    //specular *= attenuation;
    return (ambient + diffuse );
} 


void main()
{
	vec3 normal = normalize(normal_lerped);
	// vec3 lightDir = normalize(light_dir.xyz);
	// float diff = max(dot(norm, -lightDir), 0.0);
	// vec3 diffuse = diff * light_color.xyz;
	
	vec4 texture_color =texture(texture0,texture_coord);
	//color = vec4(diffuse,1.0f)*0.7+c*0.3;
	//color =texture(texture0,texture_coord)*0.5+ vec4(diffuse*sin(time.x*5.0),1.0f);
	//color =texture(texture0,texture_coord)*0.5+ vec4(diffuse,1.0f)*0.5;
	//color = c;
	//color=vec4(0.3,0.9,0.1,0.0);
	vec3 dir_color=CalcDirLight(lights[0], normal);
	vec3 point_light=CalcPointLight(lights[1], normal, frag_position);
   	color=vec4(dir_color,1.0) *vec4(point_light,1.0)*10.0;//*texture_color;
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
		name="camera_id",
		location = 1,
		type=ShaderDataType.INT,
		value={0}
	},
	{
		name="shininess",
		location = 2,
		type=ShaderDataType.FLOAT,
		value={0.9}
	}
}
