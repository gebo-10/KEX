#pragma once
#pragma once
#include<kengine/core/base/base.h>
#include "../graphics_api.h"
namespace kengine {
	enum class RenderBufferFormat {
		R8,
		R8I,
		R8UI,
		R16I,
		R16UI,
		R32I,
		R32UI,

		RG8,
		RG8I,
		RG8UI,
		RG16I,
		RG16UI,
		RG32I,
		RG32UI,

		RGB8,
		RGB565,
		RGB_A1,
		RGB_A2,
		RGB,
		RGB10_A2UI,

		RGBA,
		RGBA4,
		RGBA8,
		RGBA8I,
		RGBA8UI,
		RGBA16I,
		RGBA16UI,
		RGBA32I,
		RGBA32UI,

		SRGB8_ALPHA8,
		STENCIL_INDEX8 = GL_STENCIL_INDEX8,
		DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
		DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8,
		DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
		DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16,
		DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24,
		DEPTH_COMPONENT32F = GL_DEPTH_COMPONENT32F,
	};
	class RenderBuffer
	{
	public:
		GPUID gpu_id = 0;
		int width=0;
		int height = 0;
		RenderBuffer(int width,int height, RenderBufferFormat format, int msaa_samples=0):width(width), height(height)
		{
			glGenRenderbuffers(1, &gpu_id);
			glBindRenderbuffer(GL_RENDERBUFFER, gpu_id);
			if (msaa_samples!=0) {
				glRenderbufferStorageMultisample(GL_RENDERBUFFER, msaa_samples, (GLenum)format, width, height);
			}
			else {
				glRenderbufferStorage(GL_RENDERBUFFER, (GLenum)format, width, height);
			}
		}

		~RenderBuffer()
		{
			glDeleteRenderbuffers(1, &gpu_id);
		}
	};
	typedef shared_ptr<RenderBuffer> RenderBufferPtr;
}