#include "pipeline_state.h"
#include <kengine/core/base/color.h>
namespace kengine {
	class ClearState :public PipelineState
	{
	public:
		PipelineStateType type = PipelineStateType::CLEAR_STATE;
		Color	clear_color;
		float	clear_depth;
		int		clear_stencil;
		ClearState()
		{
		}

		~ClearState()
		{
		}

		virtual void set(PipelineStatePtr state) {
			//glClearColor(new_state.r, new_state.g, new_state.b, new_state.a);
		}
	};
}