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
			Env.event_service.listen(EventType::OnUpdate, [this](Event* e) {
				
				
			});
		}

		~MeshMorph()
		{
		}

	private:

	};
	typedef shared_ptr<MeshMorph> MeshMorphPtr;
}