#pragma once
#include "pipeline_state.h"
namespace kengine {
	class ScissorState :public PipelineState
	{
	public:
		bool enable=false;
		Rectf rect;
		ScissorState(bool enable,Rectf rect) :PipelineState(PipelineStateType::SCISSOR_STATE), enable(enable), rect(rect)
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
				glScissor(rect.x*Screen::width, rect.y * Screen::height, rect.w * Screen::width, rect.h * Screen::height);
			}
		}
	};
}