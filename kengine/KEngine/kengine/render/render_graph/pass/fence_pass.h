#pragma once
#include "pass.h"
namespace kengine {
	class FencePass :public Pass
	{
	public:
		FencePass()
		{
		}

		~FencePass()
		{
		}

		virtual void exec(Scene& scene, RenderDataPtr render_data, Pipeline& pipeline) {
			//glFinish();
			GLsync sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
			glClientWaitSync(sync, 0, 1000000);
			glDeleteSync(sync);
		}

	private:

	};

}