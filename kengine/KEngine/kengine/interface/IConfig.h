#pragma once
#include "kengine/core/base/base.h"
namespace kengine
{
	class IConfig
	{
	public:

		virtual std::any get(string name) = 0;
	};
}
