#pragma once
#include <kengine/resource/gpu/uniform_buffer.h>
#include <kengine/core/math/kmath.h>
namespace kengine {

	//#pragma pack(4)
	struct CommonUniform { //alignas
	public:
		//float time;
		vec4	light_dir;
		Color	light_color;
		Matrix v;
		Matrix p;
		Matrix pv;

		UniformBufferPtr uniform_buffer = nullptr;
		void sync() {
			if (uniform_buffer == nullptr) {
				uniform_buffer = std::make_shared<UniformBuffer>(sizeof(CommonUniform) - sizeof(UniformBufferPtr), 0 );
			}
			memcpy(uniform_buffer->data, this, sizeof(CommonUniform) - sizeof(UniformBufferPtr));
		}
	};
	//#pragma pack()
}
