#pragma once
#include <kengine/core/base/base.h>
namespace kengine{
	class GPUResource
	{
	public:
		GPUID gpu_id;
		GPUResource()
		{
		}

		virtual ~GPUResource()
		{
		}

	private:

	};
	typedef shared_ptr<GPUResource> GPUResourcePtr;
}
