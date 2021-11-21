#pragma once
#include<kengine/core/base/base.h>
#include"component.h"
#include "component/transform_component.h"
#include "component/mesh_render.h"
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
		void add_component(ComponentPtr component) {
			components.push_back(component);
		}

		ComponentPtr get_component(ComponentType type) {
			for (auto comp : components) {
				if (comp->type == type) {
					return comp;
				}
			}
		}

	private:

	};
	typedef shared_ptr<GameObject> GameObjectPtr;
	typedef weak_ptr<GameObject> GameObjectWptr;
}
