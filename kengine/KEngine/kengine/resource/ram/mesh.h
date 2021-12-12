#pragma once

#include "kengine/resource/gpu/gpu_object.h"
#include"resource.h"
namespace kengine {
    class Mesh: public Resource {
    public:
        GPUObjectPtr gpu_object;
        PrimitiveType primitive = PrimitiveType::TRIANGLE_STRIP;
        MeshBuffer indices_buffer;
        std::vector<MeshBuffer> mesh_buffers;

        inline void gpucache( ) {
            if (gpu_object == nullptr || dirty) {
                gpu_object = std::make_shared<GPUObject>(primitive, indices_buffer, mesh_buffers);
                dirty = false;
            }
        }

        inline void uncache() {
            gpu_object = nullptr;
        }

        inline void add_buffer(MeshBuffer&& mbuffer) {
            mesh_buffers.push_back(std::move( mbuffer) );
        }

        void set_indices(BufferPtr buffer,GPUType data_type= GPUType::UNSIGNED_SHORT) {
            MeshBuffer mbuf;
            mbuf.layout_index = MeshBufferType::INDICES;
            mbuf.data_type = data_type;
            //mbuf.hit = GPUBufferHit::STATIC_DRAW;
            //mbuf.need_normalized = false;
            //mbuf.component_num = 1;
            mbuf.buffer = buffer;
            //add_buffer( std::move(mbuf) );
            indices_buffer = mbuf;
        }

        void set_position(BufferPtr buffer){
            MeshBuffer mbuf;
            mbuf.layout_index = MeshBufferType::POSITION;
            mbuf.data_type = GPUType::FLOAT;
            //mbuf.hit = GPUBufferHit::STATIC_DRAW;
            //mbuf.need_normalized = false;
            mbuf.component_num = 3;
            mbuf.buffer = buffer;
            add_buffer(std::move(mbuf));
        }

        void set_normal(BufferPtr buffer) {
            MeshBuffer mbuf;
            mbuf.layout_index = MeshBufferType::NORMAL;
            mbuf.data_type = GPUType::FLOAT;
            //mbuf.hit = GPUBufferHit::STATIC_DRAW;
            mbuf.need_normalized = true; //TODO
            mbuf.component_num = 3;
            mbuf.buffer = buffer;
            add_buffer(std::move(mbuf));
        }

        void set_tangent(BufferPtr buffer) {
            MeshBuffer mbuf;
            mbuf.layout_index = MeshBufferType::TANGENT;
            mbuf.data_type = GPUType::FLOAT;
            //mbuf.hit = GPUBufferHit::STATIC_DRAW;
            //mbuf.need_normalized = true; ??
            mbuf.component_num = 3;
            mbuf.buffer = buffer;
            add_buffer(std::move(mbuf));
        }

        void set_color(BufferPtr buffer) {
            MeshBuffer mbuf;
            mbuf.layout_index = MeshBufferType::COLOR;
            mbuf.data_type = GPUType::FLOAT;
            //mbuf.hit = GPUBufferHit::STATIC_DRAW;
            //mbuf.need_normalized = true;
            mbuf.component_num = 3;
            mbuf.buffer = buffer;
            add_buffer(std::move(mbuf));
        }

        void set_uv(int index,BufferPtr buffer){
            MeshBuffer mbuf;
            mbuf.layout_index = (MeshBufferType)((int)MeshBufferType::UV0+ index);
            mbuf.data_type = GPUType::FLOAT;
            //mbuf.hit = GPUBufferHit::STATIC_DRAW;
            //mbuf.need_normalized = true;
            mbuf.component_num = 2;
            mbuf.buffer = buffer;
            add_buffer(std::move(mbuf));
        }
    
        void draw(int count=1) {
            //gpucache();
            if (count <= 1) {
                gpu_object->draw();
            }
            else {
                gpu_object->draw_instance(count);
            }          
        }
    };
    typedef shared_ptr<Mesh> MeshPtr;
}
