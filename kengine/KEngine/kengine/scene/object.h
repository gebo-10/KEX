#pragma once
#include<kengine/core/base/base.h>
#include"component.h"
#include "component/transform.h"
#include "component/mesh_render.h"
#include "component/mesh_skin.h"
#include "component/light.h"
namespace kengine {
	class Object
	{
	public:
		//uint32 id;
		bool active=true;
		Object * parent;
		std::vector< shared_ptr<Object> > children;
		std::vector<ComponentPtr> components;
		Object()
		{
			children.clear();
			components.clear();
		}

		virtual ~Object()
		{
		}

		bool add_component(ComponentPtr component) {
			if (get_component(component->type) != nullptr) {
				return false;
			}
			component->go = this;
			components.push_back(component);
			component->aweak();
			component->state = ComponentState::Aweak;
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

		shared_ptr<Object> get_child(int index) {
			return children[index];
		}

		void add_child(shared_ptr<Object> child) {
			child->parent = this;
			children.push_back(child);
		}

	private:

	};
	typedef shared_ptr<Object> ObjectPtr;
	typedef weak_ptr<Object> ObjectWptr;
}
