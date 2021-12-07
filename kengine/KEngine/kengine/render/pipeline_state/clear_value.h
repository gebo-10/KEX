#pragma once
#include "pipeline_state.h"
#include <kengine/core/base/color.h>
namespace kengine {
	class ClearValue :public PipelineState
	{
	public:
		Color	clear_color;
		float	clear_depth;
		int		clear_stencil;
		ClearValue(Color color, float depth, int stencil):PipelineState(PipelineStateType::CLEAR_VALUE),
			clear_color(color),
			clear_depth(depth),
			clear_stencil(clear_stencil)
		{
		}

		~ClearValue()
		{
		}

		virtual void set(PipelineStatePtr state) {
			auto new_state = std::dynamic_pointer_cast<ClearValue>(state);
			if (!(new_state->clear_color == clear_color)) {
				clear_color = new_state->clear_color;
				glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
			}
			if ( new_state->clear_depth != clear_depth) {
				clear_depth = new_state->clear_depth;
				glClearDepth(clear_depth);
			}
			if (new_state->clear_stencil != clear_stencil) {
				clear_stencil = new_state->clear_stencil;
				glClearDepth(clear_stencil);
			}
		}
	};
}