#pragma once
#include"resource.h"
#include "../gpu/gpu_texture.h"
namespace kengine {
	class Texture : public Resource
	{
	public:
		GPUTexturePtr gpu_texture=nullptr;
		TextureDesc desc;
		bool read_enable = false;
		bool write_enable = false;
		std::vector<BufferPtr> buffers;
		Texture() = delete;
		Texture(TextureDesc& desc): desc(desc){
			buffers.clear();
		}

		void add_data(BufferPtr buffer) {
			buffers.push_back(buffer);
		}

		void gpucache() {
			if (gpu_texture == nullptr || dirty) {
				if (buffers.size() == 0) {
					gpu_texture = std::make_shared<GPUTexture>(desc);
				}
				else {
					gpu_texture = std::make_shared<GPUTexture>(desc, buffers);
				}
				dirty = false;
			}
		}
		void uncache() {
			gpu_texture = nullptr;
		}
		//void bind(int bind_pont) {
		//	if (gpu_texture == nullptr) {
		//		gpucache();
		//	}
		//	gpu_texture->bind(bind_pont);
		//}
	};
	typedef shared_ptr<Texture> TexturePtr;
}