#pragma once
#include "scene.h"
#include <kengine/util/render_graph_importer.h>
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

		void init() {
			scene = std::make_shared<Scene>();
			//scene->render_graph = render.default_rg();
			scene->render_graph = RenderGraphImporter::import_default();
			//scene->render_graph = RenderGraphImporter::import_blur_rg();
			scene->init();
			
		}
		
		void update() {
			scene->update();
		}

		void load_scene(PathID id) {}
		void unload_scene(){}

		void change_scene() {}
	};
}