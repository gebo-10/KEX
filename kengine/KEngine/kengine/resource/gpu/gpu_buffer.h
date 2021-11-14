#pragma once

#include "../../render/render_api.h"
#include <kengine/core/base/base.h>

namespace kengine
{
    class GPUBuffer {
    public:
        GPUID  gpu_id;
        uint32_t size;
        int type;
        int gpu_memery_hint;
        GPUBuffer() :gpu_id(-1), size(0) {}

        void create(BufferPtr buffer, int type, int hint) {
            size = buffer->size;
            type = type;
            gpu_memery_hint = hint;
            glGenBuffers(1, &gpu_id);
            glBindBuffer(type, gpu_id);
            glBufferData(type, buffer->size, buffer->data, hint);
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
        void bind() {
            glBindBuffer(type, gpu_id);
        }
        void destroy() {
            glDeleteBuffers(1, &gpu_id);
        }
    };
    typedef shared_ptr<GPUBuffer> GPUBufferPtr;
}