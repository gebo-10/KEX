#pragma once
#include <kengine/core/base/base.h>
namespace kengine {
	enum class ComponentType {
		TRANSFORM,
		MESH_RENDER,
		MESH_MORPH,
		MESH_SKIN,
		CAMERA,
	};
	class GameObject;
	class Component
	{
	public:
		ComponentType type;
		GameObject* go;
		Component(ComponentType t):type(t)
		{
		}

		virtual ~Component()
		{
		}

		virtual void on_attach() {}
	};
	typedef shared_ptr<Component> ComponentPtr;
}