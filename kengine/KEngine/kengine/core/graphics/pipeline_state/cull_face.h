#include "pipeline_state.h"
#include <kengine/core/base/color.h>
namespace kengine {
	class CullFace :public PipelineState
	{
	public:
		PipelineStateType type = PipelineStateType::CULL_FACE;
		Face face;
		CullFace()
		{
		}

		~CullFace()
		{
		}

		virtual void set(PipelineStatePtr state) {
			switch (face)
			{
			case Face::FRONT:
				//glDisable(GL_CULL_FACE);
				break;
			case Face::BACK:
				//glEnable(GL_CULL_FACE);
				//glCullFace(GL_BACK);
				break;
			case Face::FRONT_AND_BACK:
				//glEnable(GL_CULL_FACE);
				//glCullFace(GL_FRONT);
				break;
			default:
				break;
			}
		}
	};
}