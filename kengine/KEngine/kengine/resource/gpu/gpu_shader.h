#pragma once
#include "gpu_resource.h"
#include "gpu_buffer.h"
namespace kengine {
	class GPUShader
	{
	public:
		GPUShader()
		{
		}

		~GPUShader()
		{
		}

	private:

	};

	
	typedef shared_ptr<GPUShader> GPUShaderPtr;
}