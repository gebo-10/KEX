#pragma once
#include "../../core/graphics/graphics.h"
#include "kengine/resource/gpu/gpu_object.h"

namespace kengine {
    class Mesh {
    public:
        GPUObjectPtr gpu_object;
        PrimitiveType primitive = PRIMITIVE_TRIANGLES;
        std::map<MeshBufferType,MeshBuffer> mesh_buffer;

        void add_buffer(MeshBuffer&& mbuffer) {
            mesh_buffer[mbuffer.type] = mbuffer;
        }
        void add_buffer(BufferPtr buffer, MeshBufferType type) {}

        void set_indices(BufferPtr buffer) {
            MeshBuffer mbuf;
            mbuf.type = MeshBufferType::INDICES;
            mbuf.data_type = GPUType::UNSIGNED_SHORT;
            //mbuf.hit = GPUBufferHit::STATIC_DRAW;
            //mbuf.need_normalized = false;
            //mbuf.component_num = 1;
            mbuf.buffer = buffer;
            add_buffer( std::move(mbuf) );
        }

        void set_position(BufferPtr buffer){
            MeshBuffer mbuf;
            mbuf.type = MeshBufferType::POSITION;
            mbuf.data_type = GPUType::FLOAT;
            //mbuf.hit = GPUBufferHit::STATIC_DRAW;
            //mbuf.need_normalized = false;
            mbuf.component_num = 3;
            mbuf.buffer = buffer;
            add_buffer(std::move(mbuf));
        }

        void set_normal(BufferPtr buffer) {
            MeshBuffer mbuf;
            mbuf.type = MeshBufferType::NORMAL;
            mbuf.data_type = GPUType::FLOAT;
            //mbuf.hit = GPUBufferHit::STATIC_DRAW;
            mbuf.need_normalized = true;
            mbuf.component_num = 3;
            mbuf.buffer = buffer;
            add_buffer(std::move(mbuf));
        }

        void set_tangent(BufferPtr buffer) {
            MeshBuffer mbuf;
            mbuf.type = MeshBufferType::TANGENT;
            mbuf.data_type = GPUType::FLOAT;
            //mbuf.hit = GPUBufferHit::STATIC_DRAW;
            //mbuf.need_normalized = true; ??
            mbuf.component_num = 3;
            mbuf.buffer = buffer;
            add_buffer(std::move(mbuf));
        }

        void set_color(BufferPtr buffer) {
            MeshBuffer mbuf;
            mbuf.type = MeshBufferType::COLOR;
            mbuf.data_type = GPUType::FLOAT;
            //mbuf.hit = GPUBufferHit::STATIC_DRAW;
            //mbuf.need_normalized = true;
            mbuf.component_num = 3;
            mbuf.buffer = buffer;
            add_buffer(std::move(mbuf));
        }

        void set_uv1(BufferPtr buffer){
            MeshBuffer mbuf;
            mbuf.type = MeshBufferType::UV1;
            mbuf.data_type = GPUType::FLOAT;
            //mbuf.hit = GPUBufferHit::STATIC_DRAW;
            //mbuf.need_normalized = true;
            mbuf.component_num = 2;
            mbuf.buffer = buffer;
            add_buffer(std::move(mbuf));
        }

        void set_uv2(BufferPtr buffer) {
            MeshBuffer mbuf;
            mbuf.type = MeshBufferType::UV2;
            mbuf.data_type = GPUType::FLOAT;
            //mbuf.hit = GPUBufferHit::STATIC_DRAW;
            //mbuf.need_normalized = true;
            mbuf.component_num = 2;
            mbuf.buffer = buffer;
            add_buffer(std::move(mbuf));
        }
    };
}
