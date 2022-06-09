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
		ARCBALL_MONITOR,
		GRID_MAP,
	};
	enum class ComponentState {
		Undefine,
		Aweak,
		Start,
		Destory,
	};
	class Object;
	class Component
	{
	public:
		ComponentState state= ComponentState::Undefine;
		ComponentType type;
		Object* go;
		Component(ComponentType t):type(t)
		{
		}

		virtual ~Component()
		{
		}

		virtual void aweak() {}
		virtual void start(){}
		virtual void dettach() {}
		virtual void update(){}
	};
	typedef shared_ptr<Component> ComponentPtr;
}