#pragma once
#include"../component.h"
#include <kengine/resource/ram/mesh.h>
#include <kengine/resource/ram/material.h>
#include <kengine/environment.h>
namespace kengine {
	class MeshMorph :public Component
	{
	public:
		MeshPtr mesh;
		MaterialPtr material;
		int instance_count = 1;
		std::vector<float> blend_key;
		MeshMorph() :Component(ComponentType::MESH_MORPH)
		{

		}

		~MeshMorph()
		{
		}

	private:

	};
	typedef shared_ptr<MeshMorph> MeshMorphPtr;
}