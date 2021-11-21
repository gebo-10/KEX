#pragma once
#include"../component.h"
#include <kengine/core/math/kmath.h>
namespace kengine {
	class TransformComponent :public Component
	{
	public:
		Transform transform;
		TransformComponent():Component(ComponentType::TRANSFORM)
		{
		}

		~TransformComponent()
		{
		}

	private:

	};
	typedef shared_ptr<TransformComponent> TransformComponentPtr;
}