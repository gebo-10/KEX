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

		RenderGraphPtr default_rg() {
			RenderGraphPtr render_graph = std::make_shared<RenderGraph>();
			auto state_pass = std::make_shared<StatePass>();
			state_pass->states.push_back(std::make_shared<ScissorState>(true, Rectf(0,0,1,1)));
			state_pass->states.push_back( std::make_shared<ClearValue>(color_green, 1.0f, 0) );
			state_pass->states.push_back( std::make_shared<DepthTest>(true,CompareFunc::LESS) );
			render_graph->passes.push_back(state_pass);

			render_graph->passes.push_back(std::make_shared<ClearPass>(true, true, true));

			render_graph->passes.push_back(std::make_shared<DrawPass>());
			render_graph->passes.push_back(std::make_shared<FencePass>());
			auto dp2=std::make_shared<DrawPass>();
			dp2->camera_id = 1;
			render_graph->passes.push_back(dp2);

			//{
			//	auto state_pass = std::make_shared<StatePass>();
			//	state_pass->states.push_back(std::make_shared<ScissorState>(true, Rectf(0, 0, 1, 1)));
			//	state_pass->states.push_back(std::make_shared<ClearValue>(color_green, 0, 0));
			//	render_graph->passes.push_back(state_pass);
			//}
			return render_graph;
		}

		void update(Scene &scene) {
			scene.render_graph->exec(scene);
		}
	private:

	};

}