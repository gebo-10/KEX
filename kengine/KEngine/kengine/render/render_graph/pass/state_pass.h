#pragma once
#include "../pass.h"
namespace kengine {
	class StatePass :public Pass
	{
	public:
		std::vector<PipelineStatePtr> states;
		StatePass()
		{
		}

		~StatePass()
		{
		}

		virtual void exec(ScenePtr scene) {}

	};

}