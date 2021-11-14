#pragma once
#include "gpu_resource.h"
#include "gpu_buffer.h"
namespace kengine {
	class GPUImage
	{
	public:
		int type = GL_TEXTURE_2D;
		GPUID gpu_id = -1;
		virtual bool create(void* data, int width, int height,  int format, int internal_format) {
			glGenTextures(1, &gpu_id);
			glBindTexture(GL_TEXTURE_2D, gpu_id);
			glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			return true;
		}
		void update(void* data, int width, int height, int format, int internal_format) {
			glBindTexture(GL_TEXTURE_2D, gpu_id);
			glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		}

		void bind(int index) {
			//glEnable(GL_TEXTURE_2D);
			glActiveTexture(GL_TEXTURE0 + index);
			glBindTexture(type, gpu_id);
		}
		void unbind(void) {
			glBindTexture(type, 0);
		}

		void destroy() {
			glDeleteTextures(1, &gpu_id);
		}

		void set_param(int target, int name, int param) {
			glTexParameteri(target, name, param);
		}
	};
	typedef shared_ptr<GPUImage> GPUImagePtr;
}
