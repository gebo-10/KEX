#pragma once
#include "resource.h"
#include "kengine/resource/ram/shader.h"
#include <kengine/core/math/kmath.h>
#include <kengine/resource/ram/texture.h>
namespace kengine {   
    struct Uniform {
        bool dirty = false;
        GPUType type;
        int location = -1;
        BufferPtr buffer;
        Uniform(int location, GPUType type, int count):type(type),location(location)
        {
            int value_size = TypeInfo::gpu_type_size(type) * count;
            buffer = std::make_shared<Buffer>(value_size);
        }

        void set(void* value) {
            if (memcmp(buffer->data, value, buffer->size) == 0) return;
            std::memcpy(buffer->data, value, buffer->size);
            dirty = true;
        }

        template<typename T>
        void set(T &value) {
            set(glm::value_ptr(value));
        }

        void set(Color& value) {
            set(&value);
        }

        void sync(ShaderPtr shader) {
            if (!dirty) return;
            dirty = false;
            int count = buffer->size/TypeInfo::gpu_type_size(type);
            switch (type)
            {
            case kengine::GPUType::INT:
                glUniform1iv(location, count, (GLint*)buffer->data);
                break;
            case kengine::GPUType::UNSIGNED_INT:
                glUniform1uiv(location, count,(GLuint *) buffer->data);
                break;
            case kengine::GPUType::FLOAT:
                glUniform1fv(location, count, (GLfloat*)buffer->data);
                break;
            default:
                break;
            }
        }
    };
}