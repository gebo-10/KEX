#pragma once
#include "pass/pass.h"
#include "target.h"

#include "pass/clear_pass.h"
#include "pass/state_pass.h"
namespace kengine {
	class RenderGraph
	{
	public:
		Pipeline pipeline;
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