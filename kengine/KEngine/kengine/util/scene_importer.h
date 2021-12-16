#pragma once
#include <kengine/scene/scene.h>
namespace kengine {
	class RenderGraphImporter
	{
	public:
		static ScenePtr import(const string& filename) {
			ScenePtr scene = std::make_shared<Scene>();
			
		}
	};
}