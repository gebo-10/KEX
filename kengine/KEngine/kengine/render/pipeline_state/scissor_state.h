#pragma once
#include "pipeline_state.h"
namespace kengine {
	class ScissorState :public PipelineState
	{
	public:
		bool enable=false;
		Rect rect;
		ScissorState(bool enable,Rect rect) :PipelineState(PipelineStateType::SCISSOR_STATE), enable(enable), rect(rect)
		{
		}

		~ScissorState()
		{
		}

		virtual void set(PipelineStatePtr state) {
			auto new_state = std::dynamic_pointer_cast<ScissorState>(state);
			if (enable != new_state->enable) {
				enable = new_state->enable;
				if (enable) {
					glEnable(GL_SCISSOR_TEST);
				}
				else {
					glDisable(GL_SCISSOR_TEST);
				}
			}

			if (rect != new_state->rect) {
				rect = new_state->rect;
				glScissor(rect.x, rect.y, rect.w, rect.h);
			}
		}
	};
}