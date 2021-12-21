#pragma once
#include"../component.h"
#include <kengine/resource/ram/mesh.h>
#include <kengine/resource/ram/material.h>
#include "mesh_render.h"
#include <kengine/environment.h>
namespace kengine {
    struct SRTKey
    {
        float time;
        SRT srt;
    };
    struct SRTKeyAnimation {
        float duration;
        float ticks_per_second;
        std::map<int, std::vector<SRTKey> > bone_keys;
    };

    struct BoneWeight {
        int32 bone_id=-1;
        float weight=0;
    };
    struct VertexBoneData {
        BoneWeight weights[8];
    };

    struct Bone
    {
        bool dirty = true;
        int32 bone_id = -1;
        mat4 offset_matrix = mat4(1.0f);
        mat4 local_matrix = mat4(1.0f);
        mat4 animation_matrix = mat4(1.0f);
        mat4 global_matrix = mat4(1.0f);
        //mat4 final_matrix = mat4(1.0f);
        std::vector< shared_ptr<Bone> > children;
    };
    typedef shared_ptr<Bone> BonePtr;

    class MeshSkin :public Component
    {
    public:
        MeshPtr mesh;
        BonePtr bone_root = nullptr;
        std::vector<BonePtr> bones;
        std::vector<VertexBoneData> vertex_bone_data;
        std::vector<SRTKeyAnimation> animations;

        mat4 global_inverse_matrix = mat4(1.0f);
       
        GPUBufferPtr vertex_bone_data_ssbo;
        GPUBufferPtr bone_matrix_ssbo;
        MaterialPtr compute_material;

        MeshSkin() :Component(ComponentType::MESH_SKIN) {}
        ~MeshSkin(){}
        virtual void on_attach() {
            Env.event_setvice.listen(EventType::OnUpdate, [this](Event* e) {
                update();
            });
        }

        void update() {
            std::vector<mat4> bone_matrix;
            update_animation(0);
            update_bone_matrix(bone_root, mat4(1.0), bone_matrix);
            auto position_buffer=mesh->gpu_object->get_buffer((int)MeshBufferType::POSITION);
            auto Tposition = std::make_shared<GPUBuffer>(mesh->get_buffer((int)MeshBufferType::POSITION), GPUBufferType::SHADER_STORAGE_BUFFER, GPUBufferHit::STATIC_DRAW);
            auto mb = std::make_shared<Buffer>(bone_matrix.data(), bone_matrix.size() * sizeof(mat4));
            auto matrix_buffer= std::make_shared<GPUBuffer>(mb, GPUBufferType::SHADER_STORAGE_BUFFER, GPUBufferHit::STATIC_DRAW);
            
            compute_material->set_uniform(0, glm::value_ptr(global_inverse_matrix));
            compute_material->add_buffer(GPUBufferType::SHADER_STORAGE_BUFFER,0, Tposition);
            compute_material->add_buffer(GPUBufferType::SHADER_STORAGE_BUFFER,1, matrix_buffer);
            compute_material->add_buffer(GPUBufferType::SHADER_STORAGE_BUFFER,2, position_buffer);
            compute_material->attach_uniform();
            //Tposition->bind_to_point(0, GPUBufferType::SHADER_STORAGE_BUFFER);
            //matrix_buffer->bind_to_point(1, GPUBufferType::SHADER_STORAGE_BUFFER);
            //position_buffer->bind_to_point(2, GPUBufferType::SHADER_STORAGE_BUFFER);
            //compute_material->shader->bind();
            //compute_material->shader->gpu_shader-> set_uniform(0, glm::value_ptr(global_inverse_matrix));
            
            //glDispatchCompute(x, y, z);
        }

        void update_animation(int channel) {
            SRTKeyAnimation& a = animations[channel];
            for (auto& bone_key : a.bone_keys) {
                auto& bone=bones[bone_key.first];
                bone->animation_matrix = bone_key.second[1].srt.matrix();//TODO
                bone->dirty = true;
            }
        }

        void update_bone_matrix(BonePtr bone, mat4 parent_mat, std::vector<mat4>& bone_matrix) {
            if (bone->dirty) {
                bone->global_matrix = parent_mat * bone->animation_matrix;
                bone->dirty = false;
            }

            mat4 m = global_inverse_matrix * bone->global_matrix * bone->offset_matrix;
            bone_matrix[bone->bone_id] = m;

            for (auto child : bone->children) {
                update_bone_matrix(child, bone->global_matrix, bone_matrix);
            }
        }
    };
    typedef shared_ptr<MeshSkin> MeshSkinPtr;
}