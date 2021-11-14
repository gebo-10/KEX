#pragma once
#undef RGB
#include <kengine/core/base/base.h>
#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/minireflect.h>

#include <kengine/kserialize/common_generated.h>
#include <kengine/kserialize/assetbundle_generated.h>
#include <kengine/kserialize/shader_generated.h>

#include"../ram/shader.h"
#include"asset_common.h"
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
		void deserialize(AssetType type,BufferPtr buffer){
			switch (type)
			{
			case AssetType::TEXTURE:
				break;
			case AssetType::SHADER:
				deserialize_shader(buffer);
				break;
			case AssetType::MATERIAL:
				break;
			case AssetType::MESH:
				break;
			case AssetType::MODEL:
				break;
			case AssetType::PREFABS:
				break;
			default:
				break;
			}
		}

		void deserialize_conmmon(std::shared_ptr<kserialize::AssetCommon>& common) {
			type =(AssetType) common->asset_type();
			memery_type = (MemeryType)common->memery_type();
			id = common->id();
		}

		void deserialize_shader(BufferPtr buffer) {
			auto flatbuffer_asset = std::make_shared<kserialize::ShaderT>();
			kserialize::GetShader(buffer->data)->UnPackTo(flatbuffer_asset.get());
			flat_object = flatbuffer_asset;
			deserialize_conmmon(flatbuffer_asset->asset_common);
			auto shader = std::make_shared<Shader>();
			default_resource =std::dynamic_pointer_cast<Resource>( shader);
			shader->vert_source = flatbuffer_asset->vert;
			shader->frag_source = flatbuffer_asset->frag;
		}
	};
	typedef shared_ptr<Asset> AssetPtr;
}
