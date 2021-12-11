#pragma once
#include "gpu_resource.h"
#include "gpu_buffer.h"
namespace kengine{
	enum MeshBufferType {
		POSITION,
		COLOR,
		NORMAL,
		TANGENT,
		UV0,
		UV1,
		UV2,
		UV3,
		UV4,
		UV5,
		UV6,
		UV7,
		BONEIDS,
		WEIGHTS,
		MORPH_POSITION,
		MORPH_NORMAL,
		CUSTOM1,
		CUSTOM2,
		CUSTOM3,
		CUSTOM4,
		CUSTOM5,
		INDICES,
	};

	class MeshBuffer {
	public:
		int layout_index;
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
		GPUObject(PrimitiveType primitive_type, MeshBuffer &indices_buffer, std::vector<MeshBuffer>& buffers):primitive(primitive_type)
		{
			create(indices_buffer,buffers);
		}

		~GPUObject()
		{
			unbind();
			glDeleteVertexArrays(1, &gpu_id);
		}

		void create(MeshBuffer& indices_buffer, std::vector<MeshBuffer>& buffers) {
			glGenVertexArrays(1, &gpu_id);
			glBindVertexArray(gpu_id);

			GPUBufferPtr gpu_buffer;
			indices_type = indices_buffer.data_type;
			indices_size = indices_buffer.buffer->size / (indices_type == GPUType::UNSIGNED_SHORT ? 2 : 4);
			gpu_buffer = std::make_shared<GPUBuffer>(indices_buffer.buffer, GPUBufferType::ELEMENT_ARRAY_BUFFER, indices_buffer.hit);
			gpu_buffers.push_back(gpu_buffer);

			for (auto & buffer : buffers)
			{
				auto layout_index = buffer.layout_index;
				GPUBufferPtr gpu_buffer = std::make_shared<GPUBuffer>(buffer.buffer, GPUBufferType::ARRAY_BUFFER, buffer.hit);
				glEnableVertexAttribArray((int) layout_index);
				if (buffer.data_type >= GPUType::BYTE && buffer.data_type <= GPUType::INT) {
					glVertexAttribIPointer((GLuint)layout_index, buffer.component_num, (GLenum)buffer.data_type, 0, (const GLvoid*)0);
				}
				else {
					glVertexAttribPointer((GLuint)layout_index, buffer.component_num, (GLenum)buffer.data_type, buffer.need_normalized, 0, (const GLvoid*)0);
				}
				//else if(double) {glVertexAttribLPointer(); }//TODO
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

		inline void draw_instance(int count) {
			bind();
			glDrawElementsInstanced((GLenum)primitive, indices_size, (GLenum)indices_type, 0, count);
		}
	};
	typedef shared_ptr<GPUObject> GPUObjectPtr;
}