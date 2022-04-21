#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <kengine/core/base/base.h>
#include <kengine/scene/component/mesh_skin.h>
namespace kengine {
	class SkinImporter
	{
	public:
		static MeshSkinPtr import(const std::string& pFile) {
			Assimp::Importer importer;
			const aiScene* scene;
			info("SkinImporter: {}", pFile);
			scene = importer.ReadFile(pFile, aiProcess_Triangulate
				| aiProcess_MakeLeftHanded
				//aiProcess_CalcTangentSpace |
				//| aiProcess_SortByPType
				//| aiProcess_GenSmoothNormals
				//aiProcess_LimitBoneWeights |
				//aiProcess_JoinIdenticalVertices 
			);
			if (!scene)
			{
				error("SkinImporter model error:{} {}", pFile, importer.GetErrorString());
				importer.FreeScene();
				return nullptr;
			}

			auto ai_mesh = scene->mMeshes[0];//TODO
			if (!ai_mesh->HasBones()) {
				info("  SkinImporter: has no bone");
				return nullptr;
			}
			auto skin = std::make_shared<MeshSkin>();
			

			std::map<string, BonePtr> bones;
			bones.clear();
			skin->global_inverse_matrix = glm::inverse(mat4_cast(scene->mRootNode->mTransformation));
			load_bone_tree(scene->mRootNode, bones);
			load_bone_data(ai_mesh, skin, bones);
			for (int i = 0; i < scene->mNumAnimations; i++) {
				load_bone_animation(scene->mAnimations[i], skin, bones);
			}

			skin->bones.resize(bones.size());
			for (auto& [name, bone] : bones) {
				skin->bones[bone->bone_id] = bone;
			}

			importer.FreeScene();
			info("SkinImporter: import skin success : {}", pFile);
			return skin;
		}

		static BonePtr load_bone_tree(const aiNode* ai_node, std::map<string, BonePtr>& bones) {
			string name = string(ai_node->mName.data);
			BonePtr bone = std::make_shared<Bone>();
			bone->bone_id = (int)bones.size();
			if (bones.find(name) != bones.end()) {
				error("same bone name");
			}
			bones[name] = bone;
			//info("scene node name: {}", name);
			bone->local_matrix = mat4_cast(ai_node->mTransformation);
			bone->animation_matrix = bone->local_matrix;

			bone->children.clear();
			for (int i = 0; i < ai_node->mNumChildren; i++)
			{
				auto child = load_bone_tree(ai_node->mChildren[i], bones);
				bone->children.push_back(child);
			}
			return bone;
		}

		static void load_bone_data(const aiMesh* ai_mesh, MeshSkinPtr skin, std::map<string, BonePtr>& bones) {
			std::vector < std::vector <BoneWeight> > vertex_infos;
			vertex_infos.resize(ai_mesh->mNumVertices);

			for (uint i = 0; i < ai_mesh->mNumBones; i++)
			{
				auto ai_bone = ai_mesh->mBones[i];
				auto bone = bones[string(ai_bone->mName.data)];
			
				bone->offset_matrix = mat4_cast(ai_bone->mOffsetMatrix);

				for (unsigned int weight_index = 0; weight_index < ai_bone->mNumWeights; weight_index++)
				{
					auto info = ai_bone->mWeights[weight_index];
					vertex_infos[info.mVertexId].push_back({ bone->bone_id,info.mWeight });
					if (vertex_infos[info.mVertexId].size() > 16)
					{
						error("too much bone per vertex");
					}
				}
			}

			for (int i = 0; i < vertex_infos.size(); i++) {
				auto& vertex_info = vertex_infos[i];
				VertexBoneData data;
				for (int j = 0; j < vertex_info.size(); j++) {
					data.weights[j] = vertex_info[j];
				}
				skin->vertex_bone_data.push_back(data);
			}

		}

		static void load_bone_animation(aiAnimation* aimation, MeshSkinPtr skin, std::map<string, BonePtr>& bones) {
			SRTKeyAnimation a;
			a.duration = aimation->mDuration;
			a.ticks_per_second = aimation->mTicksPerSecond;
			for (int i = 0; i < aimation->mNumChannels; i++)
			{
				string name = string(aimation->mChannels[i]->mNodeName.data);
				auto bone = bones[name];
				
				aiNodeAnim* chan = aimation->mChannels[i];
				std::vector<SRTKey> keys;
				keys.clear();
				for (int i = 0; i < chan->mNumPositionKeys; i++)
				{
					SRTKey key;
					key.time = chan->mPositionKeys[i].mTime; //WARING  TODO
					key.srt.translate = vec3_cast(chan->mPositionKeys[i].mValue);
					key.srt.scale = vec3_cast(chan->mScalingKeys[i].mValue);
					key.srt.rotate = quat_cast(chan->mRotationKeys[i].mValue);
					keys.push_back(key);
				}
				a.bone_keys[bone->bone_id] = keys;
			}
			skin->animations.push_back(a);
		}

		static inline glm::vec3 vec3_cast(const aiVector3D& v) { return glm::vec3(v.x, v.y, v.z); }
		static inline glm::vec2 vec2_cast(const aiVector3D& v) { return glm::vec2(v.x, v.y); }
		static inline glm::quat quat_cast(const aiQuaternion& q) { return glm::quat(q.w, q.x, q.y, q.z); }
		static inline glm::mat4 mat4_cast(const aiMatrix4x4& m) { return glm::transpose(glm::make_mat4(&m.a1)); }
		static inline glm::mat4 mat4_cast(const aiMatrix3x3& m) { return glm::transpose(glm::make_mat3(&m.a1)); }

	};

}