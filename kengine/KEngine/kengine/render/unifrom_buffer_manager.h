#pragma once
#include <kengine/core/math/kmath.h>
#include <kengine/resource/gpu/uniform_buffer.h>
namespace kengine {
	enum class UniformType {
		Global,
		Camera,
		Light,
	};
	struct GlobalUniform {
		float time;
	};
	struct Light {
		int32 type;
		vec4 position;
		vec4 dir;
		Color color;
	};
	struct LightUniform {
		Light lights[16];
	};
	struct Camera {
		mat4 V;
		mat4 P;
		mat4 PV;
	};
	struct CameraUniform {
		Camera cameras[4];
	};
	class UniformBufferManager
	{
	public:
		GlobalUniform global;
		UniformBufferPtr global_ubo;

		CameraUniform cameras;
		UniformBufferPtr cameras_ubo;

		LightUniform lights;
		UniformBufferPtr lights_ubo;
		UniformBufferManager()
		{
			global_ubo = std::make_shared<UniformBuffer>(sizeof(GlobalUniform), (int)UniformType::Global);
			cameras_ubo = std::make_shared<UniformBuffer>(sizeof(CameraUniform), (int)UniformType::Camera);
			lights_ubo = std::make_shared<UniformBuffer>(sizeof(LightUniform), (int)UniformType::Light);
		}

		~UniformBufferManager(){}

		void sync() {
			memcpy(global_ubo->data, this, sizeof(GlobalUniform));
			memcpy(lights_ubo->data, this, sizeof(LightUniform));
			memcpy(cameras_ubo->data, this, sizeof(CameraUniform));
		}
	};
}