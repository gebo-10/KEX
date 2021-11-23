#pragma once
#include "../asset.h"
//#include "asset_info_item.h"
#include "../asset_common.h"
#include "access_loader.h"
#include "file_access_loader.h"
#include "memery_access_loader.h"
namespace kengine
{
	class AssetBundle
	{
	public:
		enum class FileAccessType {
			FILE,
			Map,
			Memery,
		};
		FileAccessType file_access_type;
		std::unordered_map<PathID,AssetItem> asset_items;

		UID id;

		AccessLoaderPtr access_loader;

		AssetBundle(string_view path, FileAccessType access_type = FileAccessType::FILE):file_access_type(access_type){
			switch (access_type)
			{
			case FileAccessType::FILE:{
				auto file_access_loader = std::make_shared<FileAccessLoader>(path);
				//access_loader = std::dynamic_pointer_cast<AccessLoader>(file_access_loader);
				access_loader = std::dynamic_pointer_cast<AccessLoader>(file_access_loader);
				break;
			}
			case FileAccessType::Map:
				break;
			case FileAccessType::Memery:{
				std::ifstream infile;
				infile.open(path.data(), std::ios::binary | std::ios::in);
				infile.seekg(0, std::ios::end);
				int length = infile.tellg();
				infile.seekg(0, std::ios::beg);
				auto buffer = std::make_shared<Buffer>(length);
				infile.read(buffer->data, length);
				infile.close();
				auto memery_access_loader = std::make_shared<MemeryAccessLoader>(buffer);
				access_loader = std::dynamic_pointer_cast<AccessLoader>(memery_access_loader);
				break;
			}
			default:
				break;
			}
			deserialize_info(access_loader->get_info_buffer());
		}

		AssetBundle(BufferPtr buf) :file_access_type(FileAccessType::Memery) {
			auto memery_access_loader = std::make_shared<MemeryAccessLoader>(buf);
			access_loader = std::dynamic_pointer_cast<AccessLoader>(memery_access_loader);
			deserialize_info(access_loader->get_info_buffer());
		}

		~AssetBundle() {}
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		uint32 size() {
			return access_loader->bundle_size;
		}
		void serialize(){}
		void deserialize_info(BufferPtr buffer) {
			kserialize::AssetBundleT fbundle;
			kserialize::GetAssetBundle(buffer->data)->UnPackTo(&fbundle);

			for (size_t i = 0; i < fbundle.asset_infos.size(); i++)
			{
				auto info = std::move(fbundle.asset_infos[i]);
				AssetItem item{ info->id, (AssetType)info->type, info->offset, info->size, nullptr,nullptr,info->depends };
				asset_items[item.id] = std::move(item);
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		AssetPtr load_asset(AssetItem & item) {
			std::vector<AssetPtr> depends;
			for (auto depend : item.depends) {
				auto dep_asset = asset_items.find(depend);

				depends.push_back(dep_asset->second.assets);
			}
			auto asset=access_loader->load_asset(item, depends);
			//AssetsDatabase::instance().add(asset);
			return asset;
		}


		AssetPtr load_asset(PathID path) {
			auto itr=asset_items.find(path);
			if (itr == asset_items.end()) return nullptr;
			if (itr->second.assets != nullptr) {
				return itr->second.assets;
			}
			else {
				return load_asset(itr->second);
			}
		}

		std::vector<AssetPtr> load_all_asset() {
			std::vector<AssetPtr> assets;
			for (auto &info : asset_items) {
				assets.push_back(load_asset(info.second));
			}
			return assets;
		}

		bool unload_asset(PathID id) {}
		bool unload_all_asset() {}
	};
	typedef shared_ptr<AssetBundle> AssetBundlePtr;
}
