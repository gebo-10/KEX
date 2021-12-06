#pragma once
#include "gpu_buffer.h"
namespace kengine {
	class UniformBuffer
	{
	public:
		GLuint gpu_id = -1;
		int m_size = 0;
		byte* data;
		UniformBuffer(int size, uint32 binding_point)
		{
			m_size = size;
			glGenBuffers(1, &gpu_id);
			glBindBuffer(GL_UNIFORM_BUFFER, gpu_id);
			glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW); // Ô¤·ÖÅä¿Õ¼ä
			glBindBufferBase(GL_UNIFORM_BUFFER, binding_point, gpu_id);
			data =(byte*) glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
		}

		~UniformBuffer()
		{
			glBindBuffer(GL_UNIFORM_BUFFER, gpu_id);
			glUnmapBuffer(GL_UNIFORM_BUFFER);
			glDeleteBuffers(1, &gpu_id);
		}

		//void set_data(BufferPtr buffer) {
		//	glBindBuffer(GL_UNIFORM_BUFFER, gpu_id);
		//	auto pbuffer = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
		//	memcpy(pbuffer, buffer->data, buffer->size);

		//	glUnmapBuffer(GL_UNIFORM_BUFFER);
		//}
	private:

	};
	typedef shared_ptr<UniformBuffer> UniformBufferPtr;
}