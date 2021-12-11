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
			scene = importer.ReadFile(pFile,
				aiProcess_CalcTangentSpace |
				aiProcess_Triangulate |
				aiProcess_JoinIdenticalVertices |
				aiProcess_SortByPType |
				aiProcess_GenSmoothNormals
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
			if (ai_mesh->mNumFaces * 3 < 65535) {
				load_indices(ai_mesh, mesh);
			}else{
				load_indices_large(ai_mesh, mesh);
			}
			

			importer.FreeScene();
			info("MeshImporter: import success : {}", pFile);
			return mesh;
		}
		static void load_position(aiMesh* ai_mesh, MeshPtr mesh)
		{
			info("  MeshImporter: position count{}", ai_mesh->mNumVertices);
			BufferPtr buf = std::make_shared<Buffer>(ai_mesh->mNumVertices*3*sizeof(float));
			std::memcpy(buf->data, ai_mesh->mVertices, buf->size);
			mesh->set_position(buf);
		}

		static void load_normal(aiMesh* ai_mesh, MeshPtr mesh)
		{
			info("  MeshImporter: normal count{}", ai_mesh->mNumVertices);
			BufferPtr buf = std::make_shared<Buffer>(ai_mesh->mNumVertices * 3 * sizeof(float));
			std::memcpy(buf->data, ai_mesh->mNormals, buf->size);
			mesh->set_normal(buf);
		}

		static void load_uvs(aiMesh* ai_mesh, MeshPtr mesh)
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

		static void load_indices(aiMesh* ai_mesh, MeshPtr mesh)
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
			mesh->set_indices(buf);
		}

		static void load_indices_large(aiMesh* ai_mesh, MeshPtr mesh)
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
			mesh->set_indices(buf,GPUType::UNSIGNED_INT);
		}
		
	};

}