#pragma once
#include "access_loader.h"
#include <fstream>
namespace kengine {
	class FileAccessLoader:public AccessLoader
	{
	public:
		std::ifstream file;
		FileAccessLoader(string_view path)
		{
			file.open(path.data(), std::ios::binary | std::ios::in);
			file.seekg(0, std::ios::end);
			bundle_size = file.tellg();
			file.seekg(0, std::ios::beg);
		}

		~FileAccessLoader()
		{
			file.close();
		}

		BufferPtr get_info_buffer() {
			int32 info_offset = 0;
			file.read((char*)&info_offset, sizeof(int));
			//×ª»»×Ö½ÚÐò
			info_offset = Memery::ntohi(info_offset);
			int32 buffer_size = bundle_size - info_offset;
			auto buffer = std::make_shared<Buffer>(buffer_size);

			file.seekg(info_offset, std::ios::beg);
			file.read(buffer->data, buffer_size);
			return buffer;
		}

		AssetPtr load_asset( AssetItem& item, const std::vector<AssetPtr>& depends) {
			AssetPtr asset = std::make_shared<Asset>();
			item.assets = asset;
			uint32 offset = item.offset;
			uint32 size = item.size;

			file.seekg(offset, std::ios::beg);
			item.buffer = std::make_shared<Buffer>(size);
			file.read(item.buffer->data, size);

			asset->deserialize(item.type, item.buffer, depends);
			//AssetsDatabase::instance().add(asset);
			return asset;
		}

		void unload_asset(AssetItem& item) {
			item.buffer = nullptr;
			item.assets = nullptr;
		}
	};
}