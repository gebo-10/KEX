#pragma once
#include "../pipeline_state/pipeline_state.h"
#include <kengine/resource/ram/texture.h>
#include <kengine/core/math/kmath.h>
#include <kengine/scene/scene.h>
#include "pipeline.h"
namespace kengine {
	class Pass
	{
	public:
		//PipelineState state;
		std::vector<TexturePtr> input;
		RenderTargetPtr target;
		CameraPtr camera;
		std::function<std::vector<GameObject>()> cull;
		std::function<std::vector<GameObject>()> filter;
		Pass()
		{
		}

		~Pass()
		{
		}
		//virtual Matrix get_view_matrix() {}
		//virtual Matrix get_project_matrix() {}
		//virtual GameObject cull(){}
		virtual void exec(Scene& scene, Pipeline& pipeline){}
	private:

	};
	typedef shared_ptr<Pass> PassPtr;
}