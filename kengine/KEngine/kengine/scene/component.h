#pragma once
#include <kengine/core/base/base.h>
namespace kengine {
	enum class ComponentType {
		TRANSFORM,
		MESH_RENDER,
		CAMERA,
	};
	class Component
	{
	public:
		ComponentType type;
		Component(ComponentType t):type(t)
		{
		}

		virtual ~Component()
		{
		}

	private:

	};
	typedef shared_ptr<Component> ComponentPtr;
}