#pragma once
#include"../component.h"
#include <kengine/resource/ram/mesh.h>
#include <kengine/resource/ram/material.h>
namespace kengine {
	class MeshRender :public Component
	{
	public:
		MeshPtr mesh;
		MaterialPtr material;
		MeshRender() :Component(ComponentType::MESH_RENDER)
		{
		}

		~MeshRender()
		{
		}

	private:

	};
	typedef shared_ptr<MeshRender> MeshRenderPtr;
}