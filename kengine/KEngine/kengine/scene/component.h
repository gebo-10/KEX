#pragma once
#include <kengine/core/base/base.h>
namespace kengine {
	class Component
	{
	public:
		Component()
		{
		}

		virtual ~Component()
		{
		}

	private:

	};
	typedef shared_ptr<Component> ComponentPtr;
}