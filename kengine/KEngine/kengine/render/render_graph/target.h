#pragma once
#include<kengine/core/base/base.h>
#include "attachment.h"
namespace kengine {
	class RenderTarget
	{
	public:
		std::vector<AttachmentPtr> attachments;
		

		//msaa


		RenderTarget()
		{
		}

		~RenderTarget()
		{
		}
	};
	typedef shared_ptr<RenderTarget> RenderTargetPtr;
}