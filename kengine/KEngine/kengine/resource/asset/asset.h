#pragma once
#undef RGB

#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/minireflect.h>

#include <kengine/kserialize/common_generated.h>
#include <kengine/kserialize/assetbundle_generated.h>
#include <kengine/kserialize/shader_generated.h>
#include <kengine/kserialize/mesh_generated.h>


#include <kengine/core/base/base.h>
#include"asset_common.h"
#include"../ram/shader.h"
#include"../ram/mesh.h"
#include "../ram/material.h"

#include <sol.hpp>

namespace kengine
{
	class Asset
	{
	public:
		
		AssetType type;

		enum class CacheType
		{
			DYNAMIC,
			ALWAYS,
			NEWER,
		};
		CacheType cache_type;

		enum class MemeryType
		{
			RAM,
			GPU,
			RAMGPU,R
		};
		MemeryType memery_type;

		PathID id;

		ResourcePtr default_resource;
		shared_ptr< flatbuffers::NativeTable > flat_object;

		ResourcePtr instaniate() {}

		void serialize(){}
		void deserialize(AssetType type,BufferPtr buffer, const std::vector<shared_ptr<Asset> >& depends){
			switch (type)
			{
			case AssetType::TEXTURE:
				break;
			case AssetType::SHADER:
				deserialize_shader(buffer);
				break;
			case AssetType::MATERIAL:
				deserialize_material(buffer, depends);
				break;
			case AssetType::MESH:
				deserialize_mesh(buffer);
				break;
			case AssetType::MODEL:
				break;
			case AssetType::PREFABS:
				break;
			default:
				break;
			}
		}

		//void deserialize_conmmon(std::shared_ptr<kserialize::AssetCommon>& common) {
		//	type =(AssetType) common->asset_type();
		//	memery_type = (MemeryType)common->memery_type();
		//	id = common->id();
		//}

		void deserialize_shader(BufferPtr buffer) {
			auto flatbuffer_asset = std::make_shared<kserialize::ShaderT>();
			kserialize::GetShader(buffer->data)->UnPackTo(flatbuffer_asset.get());
			flat_object = flatbuffer_asset;
			//deserialize_conmmon(flatbuffer_asset->asset_common);
			auto shader = std::make_shared<Shader>();
			default_resource =std::dynamic_pointer_cast<Resource>( shader);
			shader->vert_source = flatbuffer_asset->vert;
			shader->frag_source = flatbuffer_asset->frag;
		}

		void deserialize_mesh(BufferPtr buffer) {
			auto flatbuffer_asset = std::make_shared<kserialize::MeshT>();
			kserialize::GetMesh(buffer->data)->UnPackTo(flatbuffer_asset.get());
			flat_object = flatbuffer_asset;
			//deserialize_conmmon(flatbuffer_asset->asset_common);
			auto mesh = std::make_shared<Mesh>();
			default_resource = std::dynamic_pointer_cast<Resource>(mesh);

			BufferPtr indices_buf = std::make_shared<Buffer>(flatbuffer_asset->indices.data(), flatbuffer_asset->indices.size()*2);
			mesh->set_indices(indices_buf);

			BufferPtr position_buf = std::make_shared<Buffer>(flatbuffer_asset->position.data(), flatbuffer_asset->position.size()*3*4);
			mesh->set_position(position_buf);

			//BufferPtr indices_buf = std::make_shared<Buffer>(flatbuffer_asset->indices.data(), flatbuffer_asset->indices.size());
			//mesh->set_indices(indices_buf);

			//BufferPtr indices_buf = std::make_shared<Buffer>(flatbuffer_asset->indices.data(), flatbuffer_asset->indices.size());
			//mesh->set_indices(indices_buf);
		}
	
		void deserialize_material(BufferPtr buffer, const std::vector<shared_ptr<Asset> >& depends) {
			sol::state lua;
			auto result=lua.load_buffer(buffer->data,buffer->size);
			sol::table data = result.call();

			ShaderPtr shader = std::dynamic_pointer_cast<Shader>(depends[0]->default_resource);
			auto material = std::make_shared<Material>(shader);
			default_resource = std::dynamic_pointer_cast<Resource>(material);

			sol::table uniforms = data["uniforms"];
			for (auto item : uniforms)
			{
				sol::table uniform = item.second;
				int location=uniform["location"];
				ShaderDataType type = uniform["type"];
				material->add_uniform(location, type, uniform_value(type, uniform["value"]));
			}
		}

		std::any uniform_value(ShaderDataType type, sol::table vec) {
			switch (type)
			{
			case ShaderDataType::FLOAT:
				return (float)vec[1];
			case ShaderDataType::Color:{
				auto color=Color((float)vec[1], (float)vec[2], (float)vec[3], (float)vec[4] );
				return color;
			}
			default:
				break;
			}
		}
	};
	typedef shared_ptr<Asset> AssetPtr;
}
