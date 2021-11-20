#pragma once
#include "pass.h"
#include "target.h"
namespace kengine {
	class RenderGraph
	{
	public:
		std::vector<TexturePtr> textures;
		std::vector<RenderTargetPtr> targets;
		std::vector<Pass> passes;
		RenderGraph()
		{
		}

		~RenderGraph()
		{
		}
		void exec(ScenePtr scene) {
			for (auto pass : passes) {
				pass.exec(scene);
			}
		}
	};

}