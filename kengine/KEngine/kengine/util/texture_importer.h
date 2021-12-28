#pragma once
#include <kengine/resource/ram/texture.h>

namespace kengine {
	class TextureImporter
	{
	public:
		static TexturePtr import(const string &filename, bool flip = false);

		static void save(const string& path, int width, int height, int component, void* data);
	};
}