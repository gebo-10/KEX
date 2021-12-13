#pragma once
#include <kengine/core/math/kmath.h>
namespace kengine {

	//#pragma pack(4)
	struct CommonUniform { //alignas
	public:
		vec4 time;
		vec4	light_dir;
		Color	light_color;
		Matrix v;
		Matrix p;
		Matrix pv;

		GPUBufferPtr uniform_buffer = nullptr;
		void sync() {
			if (uniform_buffer == nullptr) {
				uniform_buffer = std::make_shared<GPUBuffer>(sizeof(CommonUniform) - sizeof(GPUBufferPtr), GPUBufferType::UNIFORM_BUFFER, GPUBufferHit::DYNAMIC_DRAW);
				uniform_buffer->bind_to_point(0);
				uniform_buffer->map(GPUBufferHit::WRITE_ONLY);
			}
			memcpy(uniform_buffer->map_data, this, sizeof(CommonUniform) - sizeof(GPUBufferPtr));
		}
	};
	//#pragma pack()
}
