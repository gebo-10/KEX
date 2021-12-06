#pragma once
#include "pipeline_state.h"
namespace kengine {
	class StencilTest :public PipelineState
	{
	public:
		bool enable = false;
		StencilTest(bool enable) :PipelineState(PipelineStateType::STENCIL_TEST), enable(enable){}

		~StencilTest(){}

		virtual void set(PipelineStatePtr state) {
			auto new_state = std::dynamic_pointer_cast<StencilTest>(state);
			if (enable != new_state->enable) {
				enable = new_state->enable;
				if (enable) {
					glEnable(GL_STENCIL_TEST);
				}
				else {
					glDisable(GL_STENCIL_TEST);
				}
			}
		}

	};
}