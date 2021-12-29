#pragma once
#include <kengine/core/base/base.h>
namespace kengine {
	enum class ComponentType {
		TRANSFORM,
		MESH_RENDER,
		MESH_MORPH,
		MESH_SKIN,
		CAMERA,
		LIGHT,
	};
	class Object;
	class Component
	{
	public:
		ComponentType type;
		Object* go;
		Component(ComponentType t):type(t)
		{
		}

		virtual ~Component()
		{
		}

		virtual void on_attach() {}
		virtual void on_dettach() {}
	};
	typedef shared_ptr<Component> ComponentPtr;
}