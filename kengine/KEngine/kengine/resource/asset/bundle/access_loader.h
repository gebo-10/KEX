#pragma once
#include "../asset.h"
#include "asset_info_item.h"
namespace kengine {
	class AccessLoader
	{
	public:
		uint32 bundle_size;
		AccessLoader():bundle_size(0){}
		virtual ~AccessLoader(){}

		virtual BufferPtr get_info_buffer() = 0;

		virtual AssetPtr load_asset(const std::unordered_map<PathID, AssetItem>& items, AssetItem &item) = 0;

		virtual void unload_asset(AssetItem& item) = 0;
	};
	typedef shared_ptr<AccessLoader> AccessLoaderPtr;
}