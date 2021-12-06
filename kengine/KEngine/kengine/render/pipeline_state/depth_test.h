#pragma once
#include "pipeline_state.h"
namespace kengine {
	class DepthTest :public PipelineState
	{
	public:
		bool enable=false;
		DepthTest(bool enable) :PipelineState(PipelineStateType::DEPRH_TEST), enable(enable)
		{
		}

		~DepthTest()
		{
		}

		virtual void set(PipelineStatePtr state) {
			auto new_state = std::dynamic_pointer_cast<DepthTest>(state);
			if (enable != new_state->enable) {
				enable = new_state->enable;
				if (enable) {
					glEnable(GL_DEPTH_TEST);
				}
				else {
					glDisable(GL_DEPTH_TEST);
				}
			}
		}
	};
}