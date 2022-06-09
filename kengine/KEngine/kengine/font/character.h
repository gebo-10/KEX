#pragma once
#include <kengine/core/base/base.h>
namespace kengine {
	class Character
	{
	public:
		Character()
		{
		}

		~Character()
		{
		}

		int x;
		int y;
		int w;
		int h;

		int texture_layer; //texture array layer


	};

}