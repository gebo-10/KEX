#pragma once
#include "gpu_buffer.h"
namespace kengine {
	class ShaderStorageBuffer
	{
	public:
		uint32 gpu_id = -1;
		int m_size = 0;
		byte* data;
		ShaderStorageBuffer(int size, uint32 binding_point)
		{
			m_size = size;
			glGenBuffers(1, &gpu_id);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, gpu_id);
			glBufferData(GL_SHADER_STORAGE_BUFFER, size, nullptr, GL_STATIC_DRAW); // Ô¤·ÖÅä¿Õ¼ä
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_point, gpu_id);
			data = (byte*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
		}

		~ShaderStorageBuffer()
		{
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, gpu_id);
			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
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
	typedef shared_ptr<ShaderStorageBuffer> ShaderStorageBufferPtr;
}