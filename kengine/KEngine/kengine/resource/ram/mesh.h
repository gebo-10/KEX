#pragma once
#include "../../core/graphics/graphics.h"
#include "kengine/resource/gpu/gpu_object.h"

namespace kengine {
    class Mesh {
    public:
        GPUObjectPtr gpu_object;
        PrimitiveType primitive = PRIMITIVE_TRIANGLES;
        std::map<BufferType,MeshBuffer> mesh_buffer;

        void add_buffer(MeshBuffer& mbuffer) {}
        void add_buffer(BufferPtr buffer, BufferType type) {}

        void set_indices(BufferPtr buffer) {}
        void set_position(BufferPtr buffer){}
        void set_normal(BufferPtr buffer) {}
        void set_tangent(BufferPtr buffer) {}
        void set_color(BufferPtr buffer) {}
        void set_uv1(BufferPtr buffer){}
        void set_uv2(BufferPtr buffer) {}
    };
}
