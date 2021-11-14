//检查index实际跑的增加率 是否需要增加到 64位
#pragma once
#include "type.h"
namespace kengine {
	class UID
	{
	public:
		uint64 id;
		UID()
		{
			id = gen().id;
		}
		UID(unsigned int id)
		{
			id = id;
		}

		static UID gen() {
			static uint64 index = 0;
			return UID(index++);
		}
	};
}

