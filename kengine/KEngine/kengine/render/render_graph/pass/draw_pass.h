#pragma once
#include "pass.h"

namespace kengine {
	class DrawPass :public Pass
	{
	public:
		std::vector<TexturePtr> input;
		RenderTargetPtr target= SCREEN_TARGET;

		int camera_id=0;
		//std::function<std::vector<ObjectPtr>()> cull;
		//std::function<std::vector<ObjectPtr>()> filter;
		//std::function<std::vector<ObjectPtr>()> sort;

		virtual void exec(Scene& scene, RenderDataPtr render_data, Pipeline& pipeline) {
			pipeline.set_target(target);
			auto camera = render_data->camera_datas[camera_id];
			pipeline.set_state(std::make_shared<ViewPortState>(camera.viewport) );

			pipeline.set_state(std::make_shared<ScissorState>(true, camera.viewport));
			pipeline.set_state(std::make_shared<ClearValue>(camera.clear_color, 1.0f, 0));
			glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

			int index = 0;
			for (auto &data : render_data->mesh_datas) {
				pipeline.use_material(data.material);
				pipeline.draw(camera_id, data.matrix, data.mesh, data.instance);
				index++;
			}
			return;
		}
	};
}