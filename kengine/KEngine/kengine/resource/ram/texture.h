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
		Texture() {
			buffers.clear();
		}
		void gpucache() {
			gpu_texture = std::make_shared<GPUTexture>(desc, buffers);
		}
		void uncache() {
			gpu_texture = nullptr;
		}
	};
	typedef shared_ptr<Texture> TexturePtr;
}