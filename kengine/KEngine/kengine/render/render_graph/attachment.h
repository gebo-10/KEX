#pragma once
#include<kengine/core/base/base.h>
#include <kengine/resource/ram/texture.h>
#include "render_buffer.h"
namespace kengine {
	enum class AttachmentPoint{
		DEPTH,
		STENCIL,
		DEPTH_STENCIL,
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
		TexturePtr texture = nullptr;
		RenderBufferPtr render_buffer = nullptr;
		
		Attachment()
		{

		}

		void attach() {
			if (type == AttachmentType::TEXTURE) {
				//glFramebufferTexture2D(enum target, enum attachment, enum textarget, uint texture, int level);
			}
			else {
				//glFramebufferRenderbuffer(enum target, enum attachment, enum renderbuffertarget, uint renderbuffer);
			}
		}
	};
	typedef shared_ptr<Attachment> AttachmentPtr;
}