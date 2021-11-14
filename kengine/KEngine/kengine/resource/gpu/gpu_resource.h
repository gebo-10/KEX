#pragma once
#include <kengine/core/base/base.h>
namespace kengine{
	class GPUResource
	{
	public:
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
