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
			info("import model: {}", pFile);
			scene = importer.ReadFile(pFile,
				aiProcess_CalcTangentSpace |
				aiProcess_Triangulate |
				aiProcess_JoinIdenticalVertices |
				aiProcess_SortByPType |
				aiProcess_GenSmoothNormals
			);
			if (!scene)
			{
				error("Import model error:{} {}", pFile, importer.GetErrorString());
				importer.FreeScene();
				return nullptr;
			}

			auto ai_mesh = scene->mMeshes[0];
			info("mesh num: {}", scene->mNumMeshes);
			info("bone num: {}", ai_mesh->mNumBones);
			//print_tree(scene->mRootNode);
			auto mesh = std::make_shared<Mesh>();
			load_position(ai_mesh, mesh);
			load_normal(ai_mesh, mesh);
			load_indices(ai_mesh, mesh);

			importer.FreeScene();
			info("model import success :{}", pFile);
			return mesh;
		}
		static void load_position(aiMesh* ai_mesh, MeshPtr mesh)
		{
			BufferPtr buf = std::make_shared<Buffer>(ai_mesh->mNumVertices*3*sizeof(float));
			std::memcpy(buf->data, ai_mesh->mVertices, buf->size);
			mesh->set_position(buf);
		}

		static void load_normal(aiMesh* ai_mesh, MeshPtr mesh)
		{
			BufferPtr buf = std::make_shared<Buffer>(ai_mesh->mNumVertices * 3 * sizeof(float));
			std::memcpy(buf->data, ai_mesh->mNormals, buf->size);
			mesh->set_normal(buf);
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
			BufferPtr buf = std::make_shared<Buffer>(index.size() *  sizeof(unsigned short));
			std::memcpy(buf->data, index.data(), buf->size);
			mesh->set_indices(buf);
		}
	};

}