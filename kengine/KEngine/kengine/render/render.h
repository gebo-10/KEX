#pragma once
#include "render_graph/render_graph.h"
namespace kengine {
	class Render
	{
	public:
		Render()
		{
		}

		~Render()
		{
		}

		void init() {

		}

		void update(Scene &scene) {
			scene.render_graph->exec(scene);
		}
	private:

	};

}