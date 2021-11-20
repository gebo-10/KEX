#include "pipeline_state.h"
namespace kengine {
	class DepthTest :public PipelineState
	{
	public:
		PipelineStateType type = PipelineStateType::DEPRH_TEST;
		DepthTest()
		{
		}

		~DepthTest()
		{
		}

		virtual void set(PipelineStatePtr state) {
			
		}
	};
}