#pragma once

#include <kengine/resource/ram/texture.h>
#include <kengine/core/math/kmath.h>
#include <kengine/scene/scene.h>
#include "../pipeline.h"
#include "../../pipeline_state/all_state.h"

namespace kengine {
	class Pass
	{
	public:
		Pass(){}
		virtual ~Pass(){}
		virtual void exec(Scene& scene, Pipeline& pipeline) = 0;
	private:

	};
	typedef shared_ptr<Pass> PassPtr;
}