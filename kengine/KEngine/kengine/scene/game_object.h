#pragma once
#include<kengine/core/base/base.h>
#include"component.h"
#include "component/transform.h"
#include "component/mesh_render.h"
#include "component/mesh_skin.h"
namespace kengine {
	class GameObject
	{
	public:
		//uint32 id;
		GameObject * parent;
		std::vector< shared_ptr<GameObject> > children;
		std::vector<ComponentPtr> components;
		GameObject()
		{
		}

		virtual ~GameObject()
		{
		}

		bool add_component(ComponentPtr component) {
			if (get_component(component->type) != nullptr) {
				return false;
			}
			component->go = this;
			components.push_back(component);
			component->on_attach();
			return true;
		}

		ComponentPtr get_component(ComponentType type) {
			for (auto comp : components) {
				if (comp->type == type) {
					return comp;
				}
			}
			return nullptr;
		}

		shared_ptr<GameObject> get_child(int index) {
			return children[index];
		}

		void add_child(shared_ptr<GameObject> child) {
			child->parent = this;
			children.push_back(child);
		}

	private:

	};
	typedef shared_ptr<GameObject> GameObjectPtr;
	typedef weak_ptr<GameObject> GameObjectWptr;
}
