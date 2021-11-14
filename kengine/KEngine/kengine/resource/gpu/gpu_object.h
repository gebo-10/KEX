#pragma once
#include "gpu_resource.h"
#include "gpu_buffer.h"
namespace kengine{
	enum BufferType {
		BT_POSITION,
		BT_COLOR,
		BT_NORMAL,
		BT_TANGENT,
		BT_UV0,
		BT_UV1,
		BT_BONEIDS,
		BT_WEIGHTS,
		BT_CUSTOM1,
		BT_CUSTOM2,
		BT_CUSTOM3,
		BT_CUSTOM4,
		BT_CUSTOM5,
		BT_INDICES,
	};

	class MeshBuffer {
	public:
		BufferType type;
		bool need_normalized = false;
		int data_type = GL_FLOAT;
		int component_num = 0;
		int size = 0;
		BufferPtr buffer;
	};
	class GPUObject:public GPUResource
	{
	public:
		GPUID gpu_id;
		std::vector<GPUBufferPtr> gpu_buffers;
		GPUObject(std::map<BufferType, MeshBuffer>& buffers)
		{
			create(buffers);
		}

		~GPUObject()
		{
			destroy();
		}

		void create(std::map<BufferType, MeshBuffer>& buffers) {
			glGenVertexArrays(1, &gpu_id);
			glBindVertexArray(gpu_id);

			for (auto item : buffers)
			{
				auto buffer = item.second;
				auto buffer_type = item.first;
				GPUBufferPtr gpu_buffer = std::make_shared<GPUBuffer>();
				gpu_buffers.push_back(gpu_buffer);
				if(buffer_type== BT_INDICES)
				{
					gpu_buffer->create(buffer.buffer, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
				}else
				{
					gpu_buffer->create(buffer.buffer, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
					glEnableVertexAttribArray(buffer_type);
					if (buffer.data_type == GL_FLOAT)
					{
						glVertexAttribPointer((GLuint)buffer_type, buffer.component_num, buffer.data_type, buffer.need_normalized, 0, (const GLvoid*)0);
					}
					else if (buffer.data_type == GL_INT) {
						glVertexAttribIPointer((GLuint)buffer_type, buffer.component_num, buffer.data_type, 0, (const GLvoid*)0);
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