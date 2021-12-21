#compute
#version 310 es

layout (location = 0) uniform mat4 global_inverse_matrix;
layout(std430, binding = 0) buffer TPosition
{
	vec3 tposition[];
};
layout(std430, binding = 1) buffer BoneMatrix
{
	mat4 bone_matrix[];
};
layout(std430, binding = 2) buffer OutPosition
{
	vec3 out[];
};


layout (local_size_x = 32, local_size_y = 1, local_size_z = 1) in;


void main()
{
	out[gl_LocalInvocationIndex]=tposition[gl_LocalInvocationIndex];
}
//////////////////////////////////////////////////////////////////////////////
#decl
return{
	{
		name="global_inverse_matrix",
		location = 0,
		count=1,
		type=ShaderDataType.MAT4,
		value={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	},
}
