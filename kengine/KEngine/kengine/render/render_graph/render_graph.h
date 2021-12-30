#pragma once
#include "pass/pass.h"
#include "pass/clear_pass.h"
#include "pass/state_pass.h"
#include "pass/draw_pass.h"
#include "pass/fence_pass.h"
#include "pass/copy_framebuffer_pass.h"
#include "pass/blit_pass.h"
#include "pass/lambda_pass.h"

#include "render_target.h"
namespace kengine {
	class RenderGraph
	{
	public:
		Pipeline pipeline;
		std::vector<RenderBufferPtr> render_buffers;
		std::vector<TexturePtr> textures;
		std::vector<RenderTargetPtr> targets;

		std::vector<PassPtr> passes;
		
		RenderGraph()
		{
		}

		~RenderGraph()
		{
		}
		void exec(Scene& scene) {
			CheckGLError
			pipeline.common_uniform.time = vec4(Env.time.now, 0, 0, 0);
			RenderDataPtr render_data = scene.cull();
			std::memcpy(pipeline.common_uniform.camears, render_data->camera_datas.data(), sizeof(CameraData) * render_data->camera_datas.size());
			std::memcpy(pipeline.common_uniform.lights, render_data->light_datas.data(), sizeof(LightData) * render_data->light_datas.size());
			pipeline.sync_common_uniform();
			for (auto pass : passes) {
				pass->exec(scene, render_data, pipeline);
			}
			pipeline.set_target(RenderTarget::ScreenTarget());
			CheckGLError
		}
	};
	typedef shared_ptr<RenderGraph> RenderGraphPtr;
}