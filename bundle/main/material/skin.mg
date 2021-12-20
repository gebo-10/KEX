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

layout (location = 5) uniform mat4 bones[64];

layout(std430, binding = 0) buffer boneBuffer
{
    mat4 data[];
}bones2;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 4) in vec2 uv;
layout (location = 12)in uvec4 bone_ids;
layout (location = 13)in vec4 bone_weights;

out vec3 frag_position;
out vec3 normal_lerped;
out vec2 texture_coord;

void main()
{
	mat4 BoneTransform = bones[bone_ids.x] * bone_weights.x;
    BoneTransform += bones[bone_ids.y] * bone_weights.y;
    BoneTransform += bones[bone_ids.z] * bone_weights.z;
    BoneTransform += bones[bone_ids.w] * bone_weights.w;
    vec4 PosL = BoneTransform * vec4(position, 1.0);
	vec4 word_pos=M*PosL;
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
	
	color =texture(texture0,texture_coord);
   
}

//////////////////////////////////////////////////////////////////////////////
#decl
return{
	{
		name="M",
		location = 0,
		count=1,
		type=ShaderDataType.MAT4,
		value={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	},
	{
		name="c",
		location = 1,
		count=1,
		type=ShaderDataType.Color,
		value={0.9,0.5,0.1,1}--  ,0.2,0.9,0.3,1,  0.9,0.2,0.3,1}
	},
	{
		name="bones",
		location = 5,
		count=64,
		type=ShaderDataType.MAT4,
		value={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	},
}
