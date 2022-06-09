#pragma once
#include <kengine/core/base/base.h>
#include <kengine/core/math/kmath.h>
namespace kengine {
	class InputService
	{
	public:
		InputService()
		{
		}

		~InputService()
		{
		}
		vec2 mouse_position;
		bool mouse_button[8];


	};

}