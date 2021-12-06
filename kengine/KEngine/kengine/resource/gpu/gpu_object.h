#pragma once
#include "gpu_resource.h"
#include "gpu_buffer.h"
namespace kengine{
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
	
	class GPUObject
	{
	public:
		GPUID gpu_id;
		PrimitiveType primitive;
		std::vector<GPUBufferPtr> gpu_buffers;
		int indices_size;
		GPUType indices_type;
		GPUObject(PrimitiveType primitive_type,std::map<MeshBufferType, MeshBuffer>& buffers):primitive(primitive_type)
		{
			create(buffers);
		}

		~GPUObject()
		{
			unbind();
			glDeleteVertexArrays(1, &gpu_id);
		}

		void create(std::map<MeshBufferType, MeshBuffer>& buffers) {
			glGenVertexArrays(1, &gpu_id);
			glBindVertexArray(gpu_id);

			for (auto item : buffers)
			{
				auto buffer = item.second;
				auto buffer_type = item.first;
				GPUBufferPtr gpu_buffer;
				
				if(buffer_type== MeshBufferType::INDICES)
				{
					indices_type = buffer.data_type;
					indices_size = buffer.buffer->size / (indices_type == GPUType::UNSIGNED_SHORT ? 2 : 4);
					gpu_buffer = std::make_shared<GPUBuffer>(buffer.buffer, GL_ELEMENT_ARRAY_BUFFER, (int)buffer.hit);
				}else
				{
					gpu_buffer = std::make_shared<GPUBuffer>(buffer.buffer, GL_ARRAY_BUFFER, (int)buffer.hit);
					//glEnableVertexAttribArray((int)MeshBufferType::COLOR);
					glEnableVertexAttribArray((int) buffer_type);
					if (buffer.data_type == GPUType::FLOAT)
					{
						glVertexAttribPointer((GLuint)buffer_type, buffer.component_num, (GLenum)buffer.data_type, buffer.need_normalized, 0, (const GLvoid*)0);
					}
					else if (buffer.data_type == GPUType::INT) {
						glVertexAttribIPointer((GLuint)buffer_type, buffer.component_num, (GLenum)buffer.data_type, 0, (const GLvoid*)0);
					}
				}
				gpu_buffers.push_back(gpu_buffer);
			}
			glBindVertexArray(0);
		}
		
		inline void bind() {
			assert(gpu_id != 0);
			glBindVertexArray(gpu_id);
		}

		inline void unbind(void) {
			glBindVertexArray(0);
		}

		inline void draw() {
			bind();
			glDrawElements((GLenum)primitive, indices_size, (GLenum)indices_type, 0);
		}
	};
	typedef shared_ptr<GPUObject> GPUObjectPtr;
}