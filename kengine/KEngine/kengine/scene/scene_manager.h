#pragma once
#include "scene.h"
#include "../render/render.h"
namespace kengine {
	class SceneManager
	{
	public:
		ScenePtr scene=nullptr;
		SceneManager()
		{
		}

		~SceneManager()
		{
		}

		void init(Render & render) {
			scene = std::make_shared<Scene>();
			scene->render_graph = render.default_rg();
			scene->init();
		}
		
		void load_scene(PathID id) {}
		void unload_scene(){}

		void change_scene() {}
	};
}