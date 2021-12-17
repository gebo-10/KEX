#pragma once
#include <kengine/core/base/base.h>
#include <kengine/render/graphics_api.h>

#ifdef _DEBUG
#define CheckGLError Kglut::check_gl_error();
#else
#define CheckGLError  
#endif // _DEBUG

namespace kengine {

	class Kglut
	{
	public:
		static void check_gl_error() {
			auto e = glGetError();
			switch (e)
			{
			case GL_NO_ERROR:
				break;
			case GL_INVALID_ENUM:
				error("GL Invalid Enum");
				break;
			case GL_INVALID_VALUE:
				error("GL Invalid Value");
				break;
			case GL_INVALID_OPERATION:
				error("GL Invalid Operation");
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				error("Framebuffer is incomplete");
				break;
			case GL_OUT_OF_MEMORY:
				error("GL Out Of Memory");
				break;
				//case  GL_STACK_OVERFLOW:
				//	error("GL Stack Overflow");
				//case GL_STACK_UNDERFLOW:
				//	error("GL Stack Underflow\n");
			default:
				error("Unknow error");
			};
		}
	};
}
