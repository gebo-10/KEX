#pragma once
#include<kengine/core/base/base.h>
#include"component.h"
namespace kengine {
	class GameObject
	{
	public:
		weak_ptr<GameObject> father;
		std::vector< shared_ptr<GameObject> > children;
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
