#pragma once
#include "pass.h"
namespace kengine {
	class ClearPass:public Pass
	{
	public:
		uint32 clear_mask = 0;
		ClearPass(bool color, bool depth, bool stencil)
		{
			if (color) {
				clear_mask = clear_mask | GL_COLOR_BUFFER_BIT;
			}
			if (depth) {
				clear_mask = clear_mask | GL_DEPTH_BUFFER_BIT;
			}
			if (stencil) {
				clear_mask = clear_mask | GL_STENCIL_BUFFER_BIT;
			}
		}

		virtual void exec(Scene& scene, Pipeline& pipeline) {
			glClear(clear_mask);
		}
	};
}