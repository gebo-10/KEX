#pragma once
#include "gpu_resource.h"
#include "gpu_buffer.h"
namespace kengine{
	enum class GPUType {
		BYTE = GL_BYTE,
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		SHORT = GL_SHORT,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		INT = GL_INT,
		UNSIGNED_INT = GL_UNSIGNED_INT,
		FLOAT = GL_FLOAT,
	};

	enum class MeshBufferType {
		POSITION,
		COLOR,
		NORMAL,
		TANGENT,
		UV1,
		UV2,
		BONEIDS,
		WEIGHTS,
		CUSTOM1,
		CUSTOM2,
		CUSTOM3,
		CUSTOM4,
		CUSTOM5,
		INDICES,
	};

	class MeshBuffer {
	public:
		MeshBufferType type;
		GPUType data_type = GPUType::FLOAT;
		GPUBufferHit hit = GPUBufferHit::STATIC_DRAW;
		bool need_normalized = false;
		uint8 component_num = 1;
		BufferPtr buffer;
	};
	class GPUObject:public GPUResource
	{
	public:
		GPUID gpu_id;
		std::vector<GPUBufferPtr> gpu_buffers;
		GPUObject(std::map<MeshBufferType, MeshBuffer>& buffers)
		{
			create(buffers);
		}

		~GPUObject()
		{
			destroy();
		}

		void create(std::map<MeshBufferType, MeshBuffer>& buffers) {
			glGenVertexArrays(1, &gpu_id);
			glBindVertexArray(gpu_id);

			for (auto item : buffers)
			{
				auto buffer = item.second;
				auto buffer_type = item.first;
				GPUBufferPtr gpu_buffer = std::make_shared<GPUBuffer>();
				gpu_buffers.push_back(gpu_buffer);
				if(buffer_type== MeshBufferType::INDICES)
				{
					gpu_buffer->create(buffer.buffer, GL_ELEMENT_ARRAY_BUFFER,(int) buffer.hit);
				}else
				{
					gpu_buffer->create(buffer.buffer, GL_ARRAY_BUFFER, (int)buffer.hit);
					glEnableVertexAttribArray((int) buffer_type);
					if (buffer.data_type == GPUType::FLOAT)
					{
						glVertexAttribPointer((GLuint)buffer_type, buffer.component_num, (GLenum)buffer.data_type, buffer.need_normalized, 0, (const GLvoid*)0);
					}
					else if (buffer.data_type == GPUType::INT) {
						glVertexAttribIPointer((GLuint)buffer_type, buffer.component_num, (GLenum)buffer.data_type, 0, (const GLvoid*)0);
					}
				}
			}
			glBindVertexArray(0);
		}
		void bind() {
			assert(gpu_id != 0);
			glBindVertexArray(gpu_id);
		}

		void unbind(void) {
			glBindVertexArray(0);
		}
		void destroy() {
			unbind();
			glDeleteVertexArrays(1, &gpu_id);
		}

	};
	typedef shared_ptr<GPUObject> GPUObjectPtr;
}