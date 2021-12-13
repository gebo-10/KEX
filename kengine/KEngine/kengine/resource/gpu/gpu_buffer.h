#pragma once
#include <kengine/core/base/base.h>
#include <kengine/render/gpu_type.h>
namespace kengine
{
    enum class GPUBufferType {
        UNKNOW_TYPE = -1,
        ARRAY_BUFFER = GL_ARRAY_BUFFER,
        UNIFORM_BUFFER = GL_UNIFORM_BUFFER,
        ATOMIC_COUNTER_BUFFER= GL_ATOMIC_COUNTER_BUFFER,
        COPY_READ_BUFFER= GL_COPY_READ_BUFFER,
        COPY_WRITE_BUFFER= GL_COPY_WRITE_BUFFER,
        DISPATCH_INDIRECT_BUFFER = GL_DISPATCH_INDIRECT_BUFFER,
        DRAW_INDIRECT_BUFFER = GL_DRAW_INDIRECT_BUFFER,
        ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
        PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
        PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER,
        SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER,
        TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER
    };

    enum class GPUBufferHit {
        READ_ONLY = GL_READ_ONLY,
        WRITE_ONLY = GL_WRITE_ONLY,
        READ_WRITE = GL_READ_WRITE,
        BUFFER_ACCESS = GL_BUFFER_ACCESS,
        BUFFER_MAPPED = GL_BUFFER_MAPPED,
        BUFFER_MAP_POINTER = GL_BUFFER_MAP_POINTER,
        STREAM_DRAW = GL_STREAM_DRAW,
        STREAM_READ = GL_STREAM_READ,
        STREAM_COPY = GL_STREAM_COPY,
        STATIC_DRAW = GL_STATIC_DRAW,
        STATIC_READ = GL_STATIC_READ,
        STATIC_COPY = GL_STATIC_COPY,
        DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
        DYNAMIC_READ = GL_DYNAMIC_READ,
        DYNAMIC_COPY = GL_DYNAMIC_COPY,
    };

    class GPUBuffer {
    public:
        GPUID  gpu_id=-1;
        uint32 size=0;
        int type;
        int memery_hint;
        void* map_data=nullptr;

        GPUBuffer(BufferPtr buffer, GPUBufferType buffer_type, GPUBufferHit buffer_hint):
            size(buffer->size),type((int)buffer_type),
            memery_hint((int)buffer_hint) {
            glGenBuffers(1, &gpu_id);
            glBindBuffer(type, gpu_id);
            glBufferData(type, buffer->size, buffer->data, memery_hint);
        }

        GPUBuffer(uint32 buffer_size, GPUBufferType buffer_type, GPUBufferHit buffer_hint) :
            size(buffer_size), type((int)buffer_type),
            memery_hint((int)buffer_hint) {
            glGenBuffers(1, &gpu_id);
            glBindBuffer(type, gpu_id);
            glBufferData(type, size, nullptr, memery_hint);
        }

        ~GPUBuffer() {
            unmap();
            glDeleteBuffers(1, &gpu_id);
        }

        bool set_data(BufferPtr buffer)
        {
            if (buffer->size != size) {
                error("GPU buffer update buffer->size != siz");
        	    return false;
            }
            glBindBuffer(type, gpu_id);
            glBufferSubData(type, 0, size, buffer->data);
            return true;
        }

        void bind(GPUBufferType new_type=GPUBufferType::UNKNOW_TYPE) {
            assert(gpu_id != 0);
            if (new_type != GPUBufferType::UNKNOW_TYPE) {
                type = (int)new_type;
            }
            glBindBuffer(type, gpu_id);
        }

        void bind_to_point(int binding_point, GPUBufferType new_type = GPUBufferType::UNKNOW_TYPE) {
            assert(gpu_id != 0);
            if (new_type != GPUBufferType::UNKNOW_TYPE) {
                type = (int)new_type;
            }
            bind(new_type);
            glBindBufferBase((int)type, binding_point, gpu_id);
        }

        void* map(GPUBufferHit access) {
            if (map_data == nullptr) {
                bind();
                map_data= glMapBuffer(type, (int)access);
            }
            return map_data;
        }

        void unmap() {
            if (map_data != nullptr) {
                bind();
                glUnmapBuffer(type);
                map_data = nullptr;
            }
        }
    };
    typedef shared_ptr<GPUBuffer> GPUBufferPtr;
}