#include "texture_importer.h"
#include <kengine/core/io/mmap.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
namespace kengine {
	TexturePtr kengine::TextureImporter::import(const string& filename)
	{
		MapFile tex(filename);
		int w, h, n;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load_from_memory((ubyte*)tex.data(), tex.size(), &w, &h, &n, 0);
		int size = w * h * n;

		TextureDesc desc;
		desc.width = w;
		desc.height = h;
		desc.data_format = n == 3 ? TextureDataFormat::RGB: TextureDataFormat::RGBA;
		desc.data_type = TextureDataType::UNSIGNED_BYTE;
		desc.internal_format = TextureInternalFormat::RGBA8;
		auto t = std::make_shared<Texture>(desc);
		t->add_data(std::make_shared<Buffer>(data, size, true));
		return t;
	}
}
