#pragma once
#include "access_loader.h"
#include <fstream>
namespace kengine {
	class MemeryAccessLoader :public AccessLoader
	{
	public:
		BufferPtr buffer;
		
		MemeryAccessLoader(BufferPtr buf)
		{
			buffer = buf;
			bundle_size = buffer->size;
		}

		~MemeryAccessLoader()
		{
			
		}

		BufferPtr get_info_buffer() {
			
			uint16 info_buffer_size = 0;
			std::memcpy((char*)&info_buffer_size, buffer->data, sizeof(uint16));
			//×ª»»×Ö½ÚÐò
			info_buffer_size = Memery::ntohs(info_buffer_size);
			auto buf = std::make_shared<Buffer>(buffer->data + info_buffer_size, info_buffer_size);
			return buf;
		}

		AssetPtr load_asset(AssetItem& item) {
			AssetPtr asset = std::make_shared<Asset>();
			item.assets = asset;
			uint32 offset = item.offset;
			uint32 size = item.size;
			item.buffer = buffer->view(offset, size);
			asset->deserialize(item.type, item.buffer);
			//AssetsDatabase::instance().add(asset);
			return asset;
		}

		void unload_asset(AssetItem& item) {
			item.buffer = nullptr;
			item.assets = nullptr;
		}
	};
}