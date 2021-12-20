#pragma once
#include <kengine/resource/ram/mesh.h>
namespace kengine {
	class PlaneMesh :public Mesh
	{
	public:
		float position[12] = {
			-1.0f, -1.0f, 1.0f,
			-1.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			 1.0f,  1.0f, 1.0f,
		};

		float position1[12] = {
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			 1.0f,  1.0f, -1.0f,
		};

		float color[12] = {
			1.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,0.0f,1.0f,
			1.0f,1.0f,1.0f,
		};

		float uv[8] = {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
		};
		float normal[12] = {
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
		};
		unsigned short indices[6] = {
			0,1,2,
			2,1,3,
		};
		PlaneMesh()
		{
			set_position(std::make_shared<Buffer>((void*)position, sizeof(position), false));
			set_color(std::make_shared<Buffer>((void*)color, sizeof(color), false));
			set_uv(0,std::make_shared<Buffer>((void*)uv, sizeof(uv), false));
			set_normal(std::make_shared<Buffer>((void*)normal, sizeof(normal), false));
			set_indices(PrimitiveType::TRIANGLES,std::make_shared<Buffer>((void*)indices, sizeof(indices), false));

			MeshBuffer mbuf;
			mbuf.layout_index = MeshBufferType::MORPH_POSITION;
			mbuf.component_num = 3;
			mbuf.buffer = std::make_shared<Buffer>((void*)position1, sizeof(position1), false);
			add_buffer(std::move(mbuf));
		}

		~PlaneMesh()
		{
		}

		//static MeshPtr instance() {
		//	MeshPtr mesh = std::make_shared<Mesh>();
		//	mesh->set_position(std::make_shared<Buffer>((void*)position,sizeof(position),false));
		//}
	};

}