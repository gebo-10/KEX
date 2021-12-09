#pragma once
#include "pipeline_state.h"
namespace kengine {
	class ViewPortState :public PipelineState
	{
	public:
		Rectf view_port;
		ViewPortState(Rectf rect) :PipelineState(PipelineStateType::VIEW_PORT), view_port(rect)
		{
		}

		~ViewPortState()
		{
		}

		virtual void set(PipelineStatePtr state) {
			auto new_state = std::dynamic_pointer_cast<ViewPortState>(state);
			if (view_port != new_state->view_port) {
				view_port = new_state->view_port;
				glViewport(view_port.x * Screen::width, view_port.y * Screen::height, view_port.w * Screen::width, view_port.h * Screen::height);
			}
		}
	};
}