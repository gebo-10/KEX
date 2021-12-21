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
        BoneWeight weights[16];
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
            bone_matrix.resize(bones.size());
            //update_animation(0);
            update_bone_matrix(bone_root, mat4(1.0), bone_matrix);

            mesh->gpucache();
            auto position_buffer=mesh->gpu_object->get_buffer((int)MeshBufferType::POSITION);
            auto Tposition = std::make_shared<GPUBuffer>(mesh->get_buffer((int)MeshBufferType::POSITION), GPUBufferType::SHADER_STORAGE_BUFFER, GPUBufferHit::STATIC_DRAW);
            auto mb = std::make_shared<Buffer>(glm::value_ptr(bone_matrix[0]), bone_matrix.size() * sizeof(mat4), false);
            auto matrix_buffer= std::make_shared<GPUBuffer>(mb, GPUBufferType::SHADER_STORAGE_BUFFER, GPUBufferHit::STATIC_DRAW);
            
            auto mb2 = std::make_shared<Buffer>(vertex_bone_data.data(), vertex_bone_data.size() * sizeof(VertexBoneData), false);
            auto vertex_bone_data_buffer = std::make_shared<GPUBuffer>(mb2, GPUBufferType::SHADER_STORAGE_BUFFER, GPUBufferHit::STATIC_DRAW);
            //global_inverse_matrix = glm::scale(mat4(1), vec3(1, 0.5, 1));

            compute_material->shader->gpucache();
            compute_material->bind();
            compute_material->set_uniform(0, glm::value_ptr(global_inverse_matrix));
            compute_material->add_buffer(GPUBufferType::SHADER_STORAGE_BUFFER,0, Tposition);
            compute_material->add_buffer(GPUBufferType::SHADER_STORAGE_BUFFER,1, matrix_buffer);
            compute_material->add_buffer(GPUBufferType::SHADER_STORAGE_BUFFER,2, vertex_bone_data_buffer);
            compute_material->add_buffer(GPUBufferType::SHADER_STORAGE_BUFFER,3, position_buffer);
            compute_material->attach_uniform();
            //Tposition->bind_to_point(0, GPUBufferType::SHADER_STORAGE_BUFFER);
            //matrix_buffer->bind_to_point(1, GPUBufferType::SHADER_STORAGE_BUFFER);
            //position_buffer->bind_to_point(2, GPUBufferType::SHADER_STORAGE_BUFFER);
            //compute_material->shader->bind();
            //compute_material->shader->gpu_shader-> set_uniform(0, glm::value_ptr(global_inverse_matrix));
            
            glDispatchCompute(position_buffer->size/12, 1, 1);
        }

        void update_animation(int channel) {
            static float index = 0;
           index = (index + 0.1);

            SRTKeyAnimation& a = animations[channel];
            for (auto& bone_key : a.bone_keys) {
                auto& bone=bones[bone_key.first];
                
                int i = (int)index % bone_key.second.size();
                //bone->animation_matrix = bone_key.second[10].srt.matrix();//TODO
                bone->local_matrix = bone_key.second[i].srt.matrix(); 
                bone->dirty = true;
            }
        }

        void update_bone_matrix(BonePtr bone, mat4 parent_mat, std::vector<mat4>& bone_matrix) {
            //if (bone->dirty) {
            //    bone->global_matrix = parent_mat * bone->animation_matrix;
            //    bone->dirty = false;
            //}
            bones[bone->bone_id] = bone;
            bone->global_matrix = parent_mat * bone->local_matrix;

            mat4 m = global_inverse_matrix* bone->global_matrix * bone->offset_matrix;
            bone_matrix[bone->bone_id] = m;

            for (auto child : bone->children) {
                update_bone_matrix(child, bone->global_matrix, bone_matrix);
            }
        }
    };
    typedef shared_ptr<MeshSkin> MeshSkinPtr;
}