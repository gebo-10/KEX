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

layout(location = 0) out vec4 color;

void main()
{
	vec3 norm = normalize(normal_lerped);
	vec3 lightDir = normalize(light_dir.xyz);
	float diff = max(dot(norm, -lightDir), 0.0);
	vec3 diffuse = diff * light_color.xyz;
	
	//color =texture(texture0,texture_coord);
	//color = vec4(diffuse,1.0f)*0.7+c*0.3;
	//color =texture(texture0,texture_coord)*0.5+ vec4(diffuse*sin(time.x*5.0),1.0f);
	color =texture(texture0,texture_coord)*0.5+ vec4(diffuse,1.0f)*0.5;
	//color = c;
	//color=vec4(0.3,0.9,0.1,0.0);
   
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
