#pragma once
#include<kengine/core/base/base.h>
#include"component.h"
namespace kengine {
	class GameObject
	{
	public:
		GameObjectWptr father;
		std::vector<GameObjectPtr> children;
		std::vector<ComponentPtr> components;
		GameObject()
		{
		}

		virtual ~GameObject()
		{
		}

	private:

	};
	typedef shared_ptr<GameObject> GameObjectPtr;
	typedef weak_ptr<GameObject> GameObjectWptr;
}
