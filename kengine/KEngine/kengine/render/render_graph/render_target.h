#pragma once
#include<kengine/core/base/base.h>
#include "attachment.h"
#define SCREEN_TARGET RenderTarget::ScreenTarget()
namespace kengine {
	class RenderTarget
	{
	public:
		GPUID gpu_id = 0;
		std::vector<Attachment> attachments;
		std::vector<GLenum> draw_buffers;

		RenderTarget() { //screen
			//draw_buffers.push_back(GL_BACK);
		}

		RenderTarget(std::vector<Attachment>&& ats)
		{
			check_attachment_size(ats);
			attachments = std::move(ats);
			glGenFramebuffers(1, &gpu_id);
			glBindFramebuffer(GL_FRAMEBUFFER, gpu_id);
			CheckGLError
			for (auto attachment : attachments) {
				attachment.attach();
				if (attachment.attachment_point >= AttachmentPoint::COLOR_ATTACHMENT0 && attachment.attachment_point <= AttachmentPoint::COLOR_ATTACHMENT9) {
					draw_buffers.push_back((GLenum)attachment.attachment_point);
				}
			}
			glDrawBuffers(draw_buffers.size(), draw_buffers.data());

			CheckGLError
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
		}

		~RenderTarget()
		{
			glDeleteFramebuffers(1, &gpu_id);
		}

		void check_attachment_size(std::vector<Attachment>& ats) {
			int width = ats[0].width;
			int height = ats[0].height;
			for (auto &attachment : ats) {
				if (width != attachment.width || height != attachment.height) {
					error("RenderTarget attachment size not equal");
					assert(false);
				}
			} 
		}

		void bind(int target= GL_FRAMEBUFFER) {//GL_DRAW_FRAMEBUFFER GL_READ_FRAMEBUFFER GL_FRAMEBUFFER
			glBindFramebuffer(target, gpu_id);
			//if (target == GL_FRAMEBUFFER || target == GL_DRAW_FRAMEBUFFER) {
			//	glDrawBuffers(draw_buffers.size(), draw_buffers.data());
			//}
		}

		//void unbind() {
		//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//}
		
		void check_complete(int type= GL_DRAW_FRAMEBUFFER) {
			GLenum fboStatus = glCheckFramebufferStatus(type);
			switch (fboStatus)
			{
			case GL_FRAMEBUFFER_COMPLETE:
				break;
			default:
				break;
			}
		}

		static shared_ptr<RenderTarget> ScreenTarget() {
			static shared_ptr<RenderTarget> screen = std::make_shared<RenderTarget>();
			return screen;
		}
		
	private:
		
	};
	typedef shared_ptr<RenderTarget> RenderTargetPtr;
}