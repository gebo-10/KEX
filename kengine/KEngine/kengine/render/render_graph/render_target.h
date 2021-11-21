#pragma once
#include<kengine/core/base/base.h>
#include "attachment.h"
namespace kengine {
	class RenderTarget
	{
	public:
		std::vector<Attachment> attachments;
		
		GPUID gpu_id = 0;
		int width;
		int height;

		RenderTarget(std::vector<Attachment>&& ats)
		{
			attachments = std::move(ats);
			glGenFramebuffers(1, &gpu_id);
			glBindFramebuffer(GL_FRAMEBUFFER, gpu_id);
			std::vector<GLenum> draw_buffers;
			for (auto attachment : attachments) {
				attachment.attach();
				if (attachment.attachment_point >= AttachmentPoint::COLOR_ATTACHMENT0) {
					draw_buffers.push_back((GLenum)attachment.attachment_point);
				}
			}
			glDrawBuffers(draw_buffers.size(), draw_buffers.data());
		}

		~RenderTarget()
		{
			glDeleteFramebuffers(1, &gpu_id);
		}

		void bind() {
			glBindFramebuffer(GL_FRAMEBUFFER, gpu_id);
		}

		void unbind() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	};
	typedef shared_ptr<RenderTarget> RenderTargetPtr;
}