#pragma once
#include "pass.h"

namespace kengine {
	class StatePass :public Pass
	{
	public:
		std::vector<PipelineStatePtr> states;
		StatePass()
		{
		}

		virtual void exec(Scene& scene, Pipeline& pipeline) {
			for (auto state : states) {
				pipeline.set_state(state);
			}
		}
	};
}