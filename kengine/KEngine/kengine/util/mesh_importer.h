#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <kengine/core/base/base.h>
#include <kengine/resource/ram/mesh.h>
namespace kengine {
	class MeshImporter
	{
	public:
		MeshImporter()
		{
		}

		~MeshImporter()
		{
		}

		static MeshPtr import(const std::string& pFile) {
			Assimp::Importer importer;
			const aiScene* scene;
			info("MeshImporter: {}", pFile);
			scene = importer.ReadFile(pFile, aiProcess_Triangulate
				| aiProcess_MakeLeftHanded
				//aiProcess_CalcTangentSpace |
				| aiProcess_SortByPType 
				|aiProcess_GenSmoothNormals
				//aiProcess_LimitBoneWeights |
				//aiProcess_JoinIdenticalVertices 
			);
			if (!scene)
			{
				error("MeshImporter model error:{} {}", pFile, importer.GetErrorString());
				importer.FreeScene();
				return nullptr;
			}

			auto ai_mesh = scene->mMeshes[0];
			//info("mesh num: {}", scene->mNumMeshes);
			//info("bone num: {}", ai_mesh->mNumBones);
			//ai_mesh->mAnimMeshes
			

			auto mesh = std::make_shared<Mesh>();
			load_position(ai_mesh, mesh);
			load_normal(ai_mesh, mesh);
			load_uvs(ai_mesh, mesh);

			load_bone(scene, ai_mesh, mesh);

			if (ai_mesh->mNumFaces * 3 < 65535) {
				load_indices(ai_mesh, mesh);
			}else{
				load_indices_large(ai_mesh, mesh);
			}

			/*auto am=ai_mesh->mAnimMeshes[0];
			am->*/

			importer.FreeScene();
			info("MeshImporter: import success : {}", pFile);
			return mesh;
		}
		static void load_position(const aiMesh* ai_mesh, MeshPtr mesh)
		{
			info("  MeshImporter: position count{}", ai_mesh->mNumVertices);
			BufferPtr buf = std::make_shared<Buffer>(ai_mesh->mNumVertices*3*sizeof(float));
			std::memcpy(buf->data, ai_mesh->mVertices, buf->size);
			mesh->set_position(buf);

			mesh->positions.resize(ai_mesh->mNumVertices);
			std::memcpy(mesh->positions.data(), ai_mesh->mVertices, buf->size);
		}

		static void load_normal(const aiMesh* ai_mesh, MeshPtr mesh)
		{
			if (!ai_mesh->HasNormals()) {
				info("  MeshImporter: has no normal");
				return;
			}
			info("  MeshImporter: normal count{}", ai_mesh->mNumVertices);
			BufferPtr buf = std::make_shared<Buffer>(ai_mesh->mNumVertices * 3 * sizeof(float));
			std::memcpy(buf->data, ai_mesh->mNormals, buf->size);
			mesh->set_normal(buf);
		}

		static void load_uvs(const aiMesh* ai_mesh, MeshPtr mesh)
		{
			for (int i = 0; i < ai_mesh->GetNumUVChannels();i++) {
				std::vector<float> uv;
				uv.reserve(ai_mesh->mNumVertices * 2);
				uv.clear();
				for (int j = 0; j < ai_mesh->mNumVertices; j++) {
					auto coord = ai_mesh->mTextureCoords[i][j];
					uv.push_back(coord.x);
					uv.push_back(coord.y);
				}
				info("  MeshImporter: uv{} count{}", i, uv.size());
				BufferPtr buf = std::make_shared<Buffer>(uv.size()* sizeof(float));
				std::memcpy(buf->data, uv.data(), buf->size);
				mesh->set_uv(i,buf);
			}
		}

		static void load_indices(const aiMesh* ai_mesh, MeshPtr mesh)
		{
			std::vector<unsigned short> index;
			for (unsigned int i = 0; i < ai_mesh->mNumFaces; i++) {
				const aiFace& Face = ai_mesh->mFaces[i];
				index.push_back(Face.mIndices[0]);
				index.push_back(Face.mIndices[1]);
				index.push_back(Face.mIndices[2]);
			}

			if (index.size() > 65536)
			{
				error("Mesh too large limit 65536");
				return;
			}
			info("  MeshImporter: indices count{}", index.size());
			BufferPtr buf = std::make_shared<Buffer>(index.size() *  sizeof(unsigned short));
			std::memcpy(buf->data, index.data(), buf->size);
			mesh->set_indices((PrimitiveType)ai_mesh->mPrimitiveTypes,buf);
		}

		static void load_indices_large(const aiMesh* ai_mesh, MeshPtr mesh)
		{
			info("  MeshImporter: load_indices_large");
			std::vector<unsigned int> index;
			for (unsigned int i = 0; i < ai_mesh->mNumFaces; i++) {
				const aiFace& Face = ai_mesh->mFaces[i];
				index.push_back(Face.mIndices[0]);
				index.push_back(Face.mIndices[1]);
				index.push_back(Face.mIndices[2]);
			}

			info("  MeshImporter: indices count{}", index.size());
			BufferPtr buf = std::make_shared<Buffer>(index.size() * sizeof(unsigned int));
			std::memcpy(buf->data, index.data(), buf->size);
			mesh->set_indices((PrimitiveType)ai_mesh->mPrimitiveTypes,buf,GPUType::UNSIGNED_INT);
		}
		
		static void load_bone(const aiScene* scene, const aiMesh* ai_mesh, MeshPtr mesh) {
			if (!ai_mesh->HasBones()) {
				info("  MeshImporter: has no bone");
				return;
			}

			std::map<string, BoneNodePtr> bones;
			bones.clear();
			load_bone_data(ai_mesh, mesh, bones);
			auto root = load_bone_tree(scene, nullptr, scene->mRootNode, bones);
			mesh->bone_root = root;
		}

		static void load_bone_data(const aiMesh* ai_mesh, MeshPtr mesh, std::map<string, BoneNodePtr>& bones) {
			std::vector < std::vector <VertexBoneData> > vertex_infos;
			vertex_infos.resize(ai_mesh->mNumVertices);

			for (uint id = 1; id <= ai_mesh->mNumBones; id++)
			{
				auto ai_bone = ai_mesh->mBones[id-1];

				auto ai_node = ai_bone->mNode;
				auto bone = std::make_shared<BoneNode>();
				bone->bone_id = id;
				bone->name = string(ai_bone->mName.data);
				bone->offset_matrix = mat4_cast(ai_bone->mOffsetMatrix);
				if (bones.find(bone->name) != bones.end()) {
					error("same bone");
				}
				bones[bone->name] = bone;

				info("bone name: {}", string(ai_bone->mName.data));
				for (unsigned int weight_index = 0; weight_index < ai_bone->mNumWeights; weight_index++)
				{
					auto info = ai_bone->mWeights[weight_index];
					vertex_infos[info.mVertexId].push_back({ id,info.mWeight });
					if (vertex_infos[info.mVertexId].size() > 4)
					{
						error("too much bone per vertex");
					}
				}
			}
			std::vector <glm::uvec4> bone_ids;
			std::vector <glm::vec4> bone_weights;
			bone_ids.resize(ai_mesh->mNumVertices);
			bone_weights.resize(ai_mesh->mNumVertices);
			for (int i = 0; i < vertex_infos.size();i++) {
				auto& vertex_info = vertex_infos[i];
				bone_ids[i] = glm::uvec4(0);
				bone_weights[i] = glm::vec4(0.0f);
				for (int data_index = 0; data_index < vertex_info.size(); data_index++) {
					bone_ids[i][data_index] = vertex_info[data_index].bone_id;
					bone_weights[i][data_index] = vertex_info[data_index].weight;
				}

				//bone_ids[i] = glm::uvec4(1,2,3,4);
				//bone_weights[i] = glm::vec4(0.25f, 0.25f, 0.25f, 0.25f);
			}

			BufferPtr buf_id = std::make_shared<Buffer>(bone_ids.size() * sizeof(glm::uvec4));
			std::memcpy(buf_id->data, bone_ids.data(), buf_id->size);

			BufferPtr buf_weight = std::make_shared<Buffer>(bone_weights.size() * sizeof(glm::vec4));
			std::memcpy(buf_weight->data, bone_weights.data(), buf_weight->size);
			mesh->set_bone_data(buf_id, buf_weight);


			mesh->vertex_infos.assign(vertex_infos.begin(), vertex_infos.end());
		}
		
		static BoneNodePtr load_bone_tree(const aiScene* scene, BoneNode* parent, const aiNode* ai_node, std::map<string, BoneNodePtr>& bones) {
			string name = string(ai_node->mName.data);
			auto itr = bones.find(name);
			BoneNodePtr bone = nullptr;
			if (itr == bones.end()) {
				bone = std::make_shared<BoneNode>();
				bone->bone_id = bones.size()+1;
				bone->name = name;
				bones[name] = bone;
			}
			else {
				bone = itr->second;
			}
			
			bone->parent = parent;
			bone->local_matrix = mat4_cast(ai_node->mTransformation);
			bone->global_inverse_matrix = glm::inverse(mat4_cast(scene->mRootNode->mTransformation) );
			
			
			auto ai_animation = scene->mAnimations[0];
			bone->animation.duration = ai_animation->mDuration;
			bone->animation.ticks_per_second = ai_animation->mTicksPerSecond;
			for (int i = 0; i < ai_animation->mNumChannels; i++)
			{
				if (string(ai_animation->mChannels[i]->mNodeName.data) == name)
				{
					aiNodeAnim* chan = ai_animation->mChannels[i];

					for (int i = 0; i < chan->mNumPositionKeys; i++)
					{
						SRT srt;
						srt.translate = vec3_cast(chan->mPositionKeys[i].mValue);
						srt.scale = vec3_cast(chan->mScalingKeys[i].mValue);
						srt.rotate = quat_cast(chan->mRotationKeys[i].mValue);
						bone->animation.keys.push_back(srt);
					}
				}
			}

			bone->children.clear();
			for (int i = 0; i < ai_node->mNumChildren; i++)
			{
				auto child = load_bone_tree(scene, bone.get(), ai_node->mChildren[i], bones);
				bone->children.push_back(child);
			}
			return bone;
		}

		static void load_bone_animation(const aiScene* scene, const aiNode* ai_node, std::map<string, BoneNodePtr>& bones) {
			//if (!scene->HasAnimations()) {
			//	return;
			//}

			

		}


		static inline glm::vec3 vec3_cast(const aiVector3D& v) { return glm::vec3(v.x, v.y, v.z); }
		static inline glm::vec2 vec2_cast(const aiVector3D& v) { return glm::vec2(v.x, v.y); }
		static inline glm::quat quat_cast(const aiQuaternion& q) { return glm::quat(q.w, q.x, q.y, q.z); }
		static inline glm::mat4 mat4_cast(const aiMatrix4x4& m) { return glm::transpose(glm::make_mat4(&m.a1)); }
		//static inline glm::mat4 mat4_cast(const aiMatrix4x4& m) { return glm::make_mat4(&m.a1); }
		static inline glm::mat4 mat4_cast(const aiMatrix3x3& m) { return glm::transpose(glm::make_mat3(&m.a1)); }

		//static glm::mat4 mat4_cast(const aiMatrix4x4& source)
		//{
		//	glm::mat4 to;
		//	//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
		//	to[0][0] = source.a1; to[1][0] = source.a2; to[2][0] = source.a3; to[3][0] = source.a4;
		//	to[0][1] = source.b1; to[1][1] = source.b2; to[2][1] = source.b3; to[3][1] = source.b4;
		//	to[0][2] = source.c1; to[1][2] = source.c2; to[2][2] = source.c3; to[3][2] = source.c4;
		//	to[0][3] = source.d1; to[1][3] = source.d2; to[2][3] = source.d3; to[3][3] = source.d4;
		//	return to;
		//}

		//static vec3 toglm(const aiVector3D& source) {
		//	vec3 to;
		//	to.x = source.x;
		//	to.y = source.y;
		//	to.z = source.z;
		//	return to;
		//}
	};

}