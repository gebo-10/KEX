#pragma once
#include "pass.h"

namespace kengine {
	class LambdaPass :public Pass
	{
	public:
		std::function<void(Scene& scene, Pipeline& pipeline)> fun;
		LambdaPass() = delete;
		LambdaPass(std::function<void(Scene& scene, Pipeline& pipeline)> f):fun(f) {

		}
		
		void exec(Scene& scene, Pipeline& pipeline) override {
			fun(scene, pipeline);
		}
	};
	typedef shared_ptr<LambdaPass> LambdaPassPtr;
}