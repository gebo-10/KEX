#include "pipeline_state.h"
namespace kengine {
	class StencilTest :public PipelineState
	{
	public:
		PipelineStateType type = PipelineStateType::STENCIL_TEST;
		StencilTest()
		{
		}

		~StencilTest()
		{
		}

		virtual void set(PipelineStatePtr state) {
			
		}
	};
}