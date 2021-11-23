#pragma once
#include <kengine/resource/gpu/uniform_buffer.h>
#include <kengine/core/math/kmath.h>
namespace kengine {

	//#pragma pack(4)
	struct CommonUniform { //alignas
	public:
		//float time;
		Matrix v;
		Matrix p;
		Matrix pv;

		UniformBufferPtr uniform_buffer = nullptr;
		void sync() {
			if (uniform_buffer == nullptr) {
				uniform_buffer = std::make_shared<UniformBuffer>(sizeof(CommonUniform) - sizeof(UniformBufferPtr));
			}
			memcpy(uniform_buffer->data, this, sizeof(CommonUniform) - sizeof(int));
		}
	};
	//#pragma pack()
}
