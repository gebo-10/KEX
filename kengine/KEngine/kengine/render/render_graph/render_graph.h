#pragma once
#include "pass/pass.h"
#include "pass/clear_pass.h"
#include "pass/state_pass.h"
#include "pass/draw_pass.h"
#include "pass/fence_pass.h"

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
			for (auto pass : passes) {
				pass->exec(scene,pipeline);
			}
		}
	};
	typedef shared_ptr<RenderGraph> RenderGraphPtr;
}