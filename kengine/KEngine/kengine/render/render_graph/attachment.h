#pragma once
#include<kengine/core/base/base.h>
#include <kengine/resource/ram/texture.h>
#include "render_buffer.h"
namespace kengine {
	enum class AttachmentPoint{
		DEPTH = GL_DEPTH_ATTACHMENT,
		STENCIL = GL_STENCIL_ATTACHMENT,
		DEPTH_STENCIL= GL_DEPTH_STENCIL_ATTACHMENT,
		COLOR_ATTACHMENT0 = GL_COLOR_ATTACHMENT0,
		COLOR_ATTACHMENT1 = GL_COLOR_ATTACHMENT1,
		COLOR_ATTACHMENT2 = GL_COLOR_ATTACHMENT2,
		COLOR_ATTACHMENT3 = GL_COLOR_ATTACHMENT3,
		COLOR_ATTACHMENT4 = GL_COLOR_ATTACHMENT4,
		COLOR_ATTACHMENT5 = GL_COLOR_ATTACHMENT5,
		COLOR_ATTACHMENT6 = GL_COLOR_ATTACHMENT6,
		COLOR_ATTACHMENT7 = GL_COLOR_ATTACHMENT7,
		COLOR_ATTACHMENT8 = GL_COLOR_ATTACHMENT8,
		COLOR_ATTACHMENT9 = GL_COLOR_ATTACHMENT9
	};

	enum class AttachmentType {
		TEXTURE,
		RENDER_BUFFER,
	};

	class Attachment
	{
	public:
		AttachmentType type;
		AttachmentPoint attachment_point;
		int width = 0;
		int height = 0;
		TexturePtr texture = nullptr;
		RenderBufferPtr render_buffer = nullptr;

		Attachment() = delete;

		Attachment(AttachmentPoint attachment_point, TexturePtr texture):
			type(AttachmentType::TEXTURE),
			attachment_point(attachment_point),
			width(texture->desc.width),
			height(texture->desc.height),
			texture(texture)
		{}

		Attachment(AttachmentPoint attachment_point, RenderBufferPtr render_buffer) :
			type(AttachmentType::RENDER_BUFFER),
			attachment_point(attachment_point),
			width(render_buffer->width),
			height(render_buffer->height),
			render_buffer(render_buffer)
		{}

		void attach() {
			if (type == AttachmentType::TEXTURE) {
				texture->gpucache();
				glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)attachment_point, (GLenum)texture->desc.type, texture->gpu_texture->gpu_id, 0); //TODO int level
			}
			else {
				glFramebufferRenderbuffer(GL_FRAMEBUFFER,(GLenum) attachment_point, GL_RENDERBUFFER, render_buffer->gpu_id);
			}
		}
	};
	typedef shared_ptr<Attachment> AttachmentPtr;
}