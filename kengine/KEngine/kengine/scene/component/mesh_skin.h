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
        MaterialPtr compute_material;

       
        std::vector<BonePtr> bones;
        std::vector<VertexBoneData> vertex_bone_data;
        std::vector<SRTKeyAnimation> animations;

        mat4 global_inverse_matrix = mat4(1.0f);
        std::vector<mat4> bone_matrix;
        int vertex_size = 0;
        int event_id = -1;

        GPUBufferPtr matrix_buffer;

        MeshSkin() :Component(ComponentType::MESH_SKIN) {}
        ~MeshSkin(){
            Env.event_setvice.unlisten(EventType::OnUpdate, event_id);
        }
        virtual void on_attach() {
            event_id= Env.event_setvice.listen(EventType::OnUpdate, [this](Event* e) {
                update();
            });
        }

        void init(MeshPtr mesh, MaterialPtr material) {
            set_mesh(mesh, material);
            bone_matrix.resize(bones.size() * 2);
            auto mb = std::make_shared<Buffer>(glm::value_ptr(bone_matrix[0]), bone_matrix.size() * sizeof(mat4), false);
            matrix_buffer = std::make_shared<GPUBuffer>(mb, GPUBufferType::SHADER_STORAGE_BUFFER, GPUBufferHit::STATIC_DRAW);
            //matrix_buffer->map(GPUBufferHit::WRITE_ONLY);
            compute_material->add_buffer(GPUBufferType::SHADER_STORAGE_BUFFER, 1, matrix_buffer);
        }

        void set_mesh(MeshPtr mesh, MaterialPtr material) {
            compute_material = material;
            this->mesh = mesh;
            mesh->gpucache();

            auto position_buffer = mesh->gpu_object->get_buffer((int)MeshBufferType::POSITION);
            vertex_size = position_buffer->size / 12;
            auto Tposition = std::make_shared<GPUBuffer>(mesh->get_buffer((int)MeshBufferType::POSITION), GPUBufferType::SHADER_STORAGE_BUFFER, GPUBufferHit::STATIC_DRAW);
        
            auto mb2 = std::make_shared<Buffer>(vertex_bone_data.data(), vertex_bone_data.size() * sizeof(VertexBoneData), false);
            auto vertex_bone_data_buffer = std::make_shared<GPUBuffer>(mb2, GPUBufferType::SHADER_STORAGE_BUFFER, GPUBufferHit::STATIC_DRAW);
        
            compute_material->shader->gpucache();
            //compute_material->bind();
            compute_material->set_uniform(0, glm::value_ptr(global_inverse_matrix));
            compute_material->add_buffer(GPUBufferType::SHADER_STORAGE_BUFFER, 0, Tposition);
            compute_material->add_buffer(GPUBufferType::SHADER_STORAGE_BUFFER, 2, vertex_bone_data_buffer);
            compute_material->add_buffer(GPUBufferType::SHADER_STORAGE_BUFFER, 3, position_buffer);
        }

        void update() {
            update_animation(0);
            update_bone_matrix(bones[0], mat4(1.0), bone_matrix);

            auto mb = std::make_shared<Buffer>(glm::value_ptr(bone_matrix[0]), bone_matrix.size() * sizeof(mat4), false);
            matrix_buffer->set_data(mb);
            compute_material->attach_uniform();
            glDispatchCompute(vertex_size, 1, 1);
        }

        void update_animation(int channel) {
            SRTKeyAnimation& a = animations[channel];
            float TicksPerSecond = (float)(a.ticks_per_second != 0 ? a.ticks_per_second : 25.0f);
            float TimeInTicks = Env.time.now * TicksPerSecond;
            float AnimationTime = fmod(TimeInTicks, a.duration);
            for (auto& bone_key : a.bone_keys) {
                auto& bone=bones[bone_key.first];
                bone->animation_matrix = interpolate_srt(AnimationTime, bone_key.second);
                bone->dirty = true;
            }
        }

        Matrix interpolate_srt(float time, std::vector<SRTKey>& keys) {
            if (time == 0) return keys[0].srt.matrix();
            for (int i = 0; i < keys.size()-1; i++) {
                if (time >= keys[i].time && time < keys[i + 1].time) {

                    float lerp_time = (time - keys[i].time)/ (keys[i+1].time - keys[i].time);
                    auto &srt1 = keys[i].srt;
                    auto &srt2 = keys[i + 1].srt;
                    quat r = glm::lerp(srt1.rotate, srt2.rotate, lerp_time);
                    vec3 t = glm::mix(srt1.translate, srt2.translate, lerp_time);
                    vec3 s = glm::mix(srt1.scale, srt2.scale, lerp_time);

                    mat4 identity(1.f);
                    mat4 matrix = glm::translate(identity, t) * glm::mat4_cast(r) * glm::scale(identity, s);
                    return matrix;
                }
            }
        }

        void update_bone_matrix(BonePtr bone, mat4 parent_mat, std::vector<mat4>& bone_matrix) {
            if (bone->dirty) {
                bone->global_matrix = parent_mat * bone->animation_matrix;
                bone->dirty = false;
            }
            //bone->global_matrix = parent_mat * bone->local_matrix;

            bone_matrix[bone->bone_id*2] = bone->global_matrix;
            bone_matrix[bone->bone_id*2+1] = bone->offset_matrix;

            for (auto child : bone->children) {
                update_bone_matrix(child, bone->global_matrix, bone_matrix);
            }
        }
    };
    typedef shared_ptr<MeshSkin> MeshSkinPtr;
}