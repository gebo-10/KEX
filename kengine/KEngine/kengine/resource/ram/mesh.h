#pragma once
#include "kengine/resource/gpu/gpu_object.h"
#include"resource.h"
namespace kengine {
    //struct BoneAnimation
    //{
    //    int duration;
    //    int ticks_per_second;
    //    std::vector<SRT> keys;

    //    mat4 learp(int i) {
    //        //if (keys.size() == 0) return mat4(1.0);
    //        int index = i % keys.size();
    //        auto key = keys[index];
    //        return key.matrix();
    //    }
    //};

    //struct VertexBoneData {
    //    uint bone_id;
    //    float weight;
    //};

    //struct BoneNode
    //{
    //    BoneNode* parent=nullptr;
    //    std::vector< shared_ptr<BoneNode> > children;
    //    string name;
    //    uint bone_id=0;
    //    mat4 local_matrix = mat4(1.0f);
    //    mat4 offset_matrix = mat4(1.0f);
    //    //mat4 final_matrix = mat4(1.0f);
    //    mat4 global_inverse_matrix = mat4(1.0f);
    //    BoneAnimation animation;
    //};
    //typedef shared_ptr<BoneNode> BoneNodePtr;

    class Mesh: public Resource {
    public:
        GPUObjectPtr gpu_object;
        PrimitiveType primitive = PrimitiveType::TRIANGLES;
        MeshBuffer indices_buffer;
        std::vector<MeshBuffer> mesh_buffers;
        
        //BoneNodePtr bone_root=nullptr;

        //std::vector<vec3> positions;
        //std::vector < std::vector <VertexBoneData> > vertex_infos;

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
            mesh_buffers.push_back( mbuffer );
        }

        BufferPtr get_buffer(int location) {
            for (auto& mb : mesh_buffers) {
                return mb.buffer;
            }
        }

        void set_indices(PrimitiveType primitive_type, BufferPtr buffer, GPUType data_type = GPUType::UNSIGNED_SHORT) {
            primitive = primitive_type;
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
        
        void set_bone_data(BufferPtr buffer_id, BufferPtr buffer_weight) {
            {
                MeshBuffer mbuf;
                mbuf.layout_index = MeshBufferType::BONEIDS;
                mbuf.data_type = GPUType::UNSIGNED_INT;
                mbuf.component_num = 4;
                mbuf.buffer = buffer_id;
                add_buffer(std::move(mbuf));
            }
            {
                MeshBuffer mbuf;
                mbuf.layout_index = MeshBufferType::WEIGHTS;
                mbuf.data_type = GPUType::FLOAT;
                mbuf.component_num = 4;
                mbuf.buffer = buffer_weight;
                add_buffer(std::move(mbuf));
            }
        }

        //void set_bone_tree(BoneNodePtr root, int size) {
        //    bone_root = root;

        //}

        //bool has_bone() {
        //    return bone_root != nullptr;
        //}

        //std::vector<mat4> get_bone_matrix() {
        //    std::vector<mat4> bone_matrix;
        //    bone_matrix.clear();
        //    bone_matrix.resize(64);

        //    //for (int i = 0; i < 64; i++) {
        //    //    bone_matrix[i] = mat4(1.0);
        //    //}

        //    get_bone_matrix(bone_root, mat4(1.0f) ,bone_matrix);

        //    //vec4 t(0, 0, 0, 1);
        //    //mat4 m = glm::translate(mat4(1.0), vec3(1,2,3));
        //    //vec3 t2 = m * t;

        //    //std::vector<vec3> new_pos;
        //    //for (int i = 0; i < positions.size(); i++) {
        //    //    vec4  old=vec4(positions[i],1);
        //    //    
        //    //    auto info = vertex_infos[i];
        //    //    mat4 ft(0);
        //    //    for (auto& w : info) {
        //    //        ft+= bone_matrix[w.bone_id] * w.weight;
        //    //    }
        //    //    vec4  fpos = ft * old;
        //    //    new_pos.push_back(fpos);
        //    //}

        //    //BufferPtr buf = std::make_shared<Buffer>(new_pos.size() * 3 * sizeof(float));
        //    //std::memcpy(buf->data, new_pos.data(), buf->size);
        //    //set_position(buf);
        //    //dirty = true;

        //    return bone_matrix;
        //}

        //void get_bone_matrix(BoneNodePtr node, mat4 parent_mat,std::vector<mat4> &bone_matrix) {
        //    //mat4 global_transform= parent_mat* node->local_matrix;
        //    static float i = 0;
        //    i += 0.1;
        //    mat4 global_transform;
        //    if (node->animation.keys.size() == 0) {
        //        global_transform = parent_mat * node->local_matrix;
        //    }
        //    else {
        //        global_transform = parent_mat * node->animation.learp(i);
        //    }

        //    mat4 m = node->global_inverse_matrix * global_transform * node->offset_matrix;
        //    bone_matrix[node->bone_id]=m;

        //    for (auto child : node->children) {
        //        get_bone_matrix(child, global_transform, bone_matrix);
        //    }
        //}

        void draw(int count=1) {
            //gpucache();
            if (count <= 1) {
                gpu_object->draw();
            }
            else {
                gpu_object->draw_instance(count);
            }          
        }



        //void boneTransform(float timeInSeconds, std::vector<glm::mat4>& Transforms)
        //{
        //    glm::mat4 Identity = glm::mat4(1.0f);

        //    /* Calc animation duration */
        //    unsigned int numPosKeys = m_pScene->mAnimations[currentAnimation]->mChannels[0]->mNumPositionKeys;
        //    animDuration = m_pScene->mAnimations[currentAnimation]->mChannels[0]->mPositionKeys[numPosKeys - 1].mTime;

        //    float TicksPerSecond = (float)(m_pScene->mAnimations[currentAnimation]->mTicksPerSecond != 0 ? m_pScene->mAnimations[currentAnimation]->mTicksPerSecond : 25.0f);
        //    float TimeInTicks = timeInSeconds * TicksPerSecond;
        //    float AnimationTime = fmod(TimeInTicks, animDuration);

        //    ReadNodeHeirarchy(AnimationTime, m_pScene->mRootNode, Identity);

        //    Transforms.resize(m_NumBones);

        //    for (unsigned int i = 0; i < m_NumBones; i++) {
        //        Transforms[i] = m_BoneInfo[i].FinalTransformation;
        //    }
        //}




        //void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform)
        //{
        //    std::string NodeName(pNode->mName.data);

        //    const aiAnimation* pAnimation = m_pScene->mAnimations[currentAnimation];

        //    glm::mat4 NodeTransformation = mat4_cast(pNode->mTransformation);

        //    const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

        //    if (pNodeAnim) {
        //        // Interpolate scaling and generate scaling transformation matrix
        //        aiVector3D Scaling;
        //        CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
        //        glm::vec3 scale = glm::vec3(Scaling.x, Scaling.y, Scaling.z);
        //        glm::mat4 ScalingM = glm::scale(glm::mat4(1.0f), scale);

        //        // Interpolate rotation and generate rotation transformation matrix
        //        aiQuaternion RotationQ;
        //        CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
        //        glm::quat rotation = quat_cast(RotationQ);
        //        glm::mat4 RotationM = glm::toMat4(rotation);

        //        // Interpolate translation and generate translation transformation matrix
        //        aiVector3D Translation;
        //        CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
        //        glm::vec3 translation = glm::vec3(Translation.x, Translation.y, Translation.z);
        //        glm::mat4 TranslationM = glm::translate(glm::mat4(1.0f), translation);

        //        // Combine the above transformations
        //        NodeTransformation = TranslationM * RotationM * ScalingM;
        //    }

        //    // Combine with node Transformation with Parent Transformation
        //    glm::mat4 GlobalTransformation = ParentTransform * NodeTransformation;

        //    if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
        //        unsigned int BoneIndex = m_BoneMapping[NodeName];
        //        m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * m_BoneInfo[BoneIndex].BoneOffset;
        //    }

        //    for (unsigned int i = 0; i < pNode->mNumChildren; i++) {
        //        ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
        //    }
        //}
    };
    typedef shared_ptr<Mesh> MeshPtr;
}
