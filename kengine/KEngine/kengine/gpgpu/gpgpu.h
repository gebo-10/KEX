#pragma once
#include "../resource/gpu/gpu_buffer.h"
#include "../resource/ram/material.h"
namespace kengine {
	class GPGPU
	{
	public:
		MaterialPtr material;
		GPGPU()
		{
		}

		~GPGPU()
		{
		}
		void attach_buffer(int bind_point, GPUBufferPtr buffer) {
			buffer->bind_to_point(GPUBufferType::SHADER_STORAGE_BUFFER, bind_point);
		}

		void set_material(MaterialPtr cs_material) {
			material = cs_material;
		}

		void setup(int x, int y, int z, bool wait=true) {
			//material->attach_uniform();
			glDispatchCompute(x,y,z);
			//glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
			glFinish();
		}
	};
}

//auto bundle = Env.assets_database.load_bundle("test.bundle");
//Env.assets_database.load_all_bundle_asset(bundle);
//auto mat = Env.assets_database.get_resource<Material>(NAME("Assets/Bundle/cs1.material"));
//GPGPU gpgpu;
//gpgpu.set_material(mat);
//auto ssbo = std::make_shared<GPUBuffer>(32 * 16 * 2 * sizeof(int), GPUBufferType::SHADER_STORAGE_BUFFER, GPUBufferHit::DYNAMIC_DRAW);
//gpgpu.attach_buffer(0, ssbo);
//gpgpu.setup(2, 1, 1);
//int* res = (int*)ssbo->map(GPUBufferHit::READ_ONLY);
//
//for (int i = 0; i < 32 * 16 * 2; i++)
//{
//	std::cout << res[i] << " ";
//}