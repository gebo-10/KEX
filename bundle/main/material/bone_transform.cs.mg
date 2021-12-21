#compute
#version 310 es
precision highp float;
struct mvec3{
	float x;
	float y;
	float z;
};
struct BoneWeight {
    int bone_id;
    float weight;
};
struct VertexBoneData {
    BoneWeight weights[16];
};
layout (location = 0) uniform mat4 global_inverse_matrix;

layout(std430, binding = 0) buffer TPosition
{
	mvec3 tposition[];
};
layout(std430, binding = 1) buffer BoneMatrix
{
	mat4 bone_matrix[];
};
layout(std430, binding = 2) buffer VertexBoneDataBuffer
{
	VertexBoneData bone_datas[];
};

layout(std430, binding = 3) buffer OutPosition
{
	mvec3 out_position[];
};


layout (local_size_x = 1) in;


void main()
{
	uint index=gl_WorkGroupID.x;
	mvec3 t=tposition[index];

	vec4 tmp=vec4(t.x,t.y,t.z,1.0);
	VertexBoneData bone_data=bone_datas[index];

	mat4 bone_transform=mat4(0.0);

	for (int i = 0; i<16; i++) {	
		BoneWeight weight=bone_data.weights[i];
	    if(weight.bone_id==-1){
	    	break;
	    }

	    bone_transform+=bone_matrix[weight.bone_id] * weight.weight;
	}

	//mat4 bone_transform=global_inverse_matrix;
	//tmp=global_inverse_matrix*bone_transform*tmp;
	tmp=bone_transform*tmp;
	t.x=tmp.x;
	t.y=tmp.y;
	t.z=tmp.z;
	out_position[index]=t;
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
