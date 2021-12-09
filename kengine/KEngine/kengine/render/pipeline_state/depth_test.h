#pragma once
#include "pipeline_state.h"
namespace kengine {
	class DepthTest :public PipelineState
	{
	public:
		bool enable=false;
		CompareFunc compare_func;

		DepthTest(bool enable, CompareFunc func) :PipelineState(PipelineStateType::DEPRH_TEST), enable(enable), compare_func(func)
		{
		}

		~DepthTest()
		{
		}

		virtual void set(PipelineStatePtr state) {
			auto new_state = std::dynamic_pointer_cast<DepthTest>(state);
			if (enable != new_state->enable) {
				enable = new_state->enable;
				if (enable) {
					glEnable(GL_DEPTH_TEST);
				}
				else {
					glDisable(GL_DEPTH_TEST);
				}
			}

			if (compare_func != new_state->compare_func) {
				compare_func = new_state->compare_func;
				glDepthFunc((GLenum)compare_func);
			}
		}
		void setup() override {
			if (enable) {
				glEnable(GL_DEPTH_TEST);
			}
			else {
				glDisable(GL_DEPTH_TEST);
			}
			glDepthFunc((GLenum)compare_func);
		}
	};
}