#pragma once
#include"../component.h"
#include <kengine/resource/ram/mesh.h>
namespace kengine {
	class MeshRender :public Component
	{
	public:
		MeshPtr mesh;
		MaterialPtr material;
		MeshRender()
		{
		}

		~MeshRender()
		{
		}

	private:

	};

}