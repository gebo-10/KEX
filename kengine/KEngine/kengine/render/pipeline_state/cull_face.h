#pragma once
#include "pipeline_state.h"
#include <kengine/core/base/color.h>
namespace kengine {
	class CullFace :public PipelineState
	{
	public:
		Face face;
		CullFace():PipelineState(PipelineStateType::CULL_FACE)
		{
		}

		~CullFace()
		{
		}

		void set (PipelineStatePtr state) override{
			switch (face)
			{
			case Face::NONE:
				glDisable(GL_CULL_FACE);
				break;
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
		void setup() override {
			
		}
	};
}