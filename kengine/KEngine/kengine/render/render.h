#pragma once
#include "render_graph/render_graph.h"
namespace kengine {
	class Render
	{
	public:
		RenderGraphPtr render_graph;
		Render()
		{
		}

		~Render()
		{
		}

		void init() {
			render_graph = std::make_shared<RenderGraph>();
			auto state_pass = std::make_shared<StatePass>();
			auto clear_value = std::make_shared<ClearValue>(color_antiquewhite, 0, 0);
			state_pass->states.push_back(clear_value);

			render_graph->passes.push_back(state_pass);
			render_graph->passes.push_back(std::make_shared<ClearPass>(true, true, true));
		}

		void update() {
			Scene scene;
			render_graph->exec(scene);
		}
	private:

	};

}