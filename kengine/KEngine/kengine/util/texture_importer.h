#pragma once
#include <kengine/resource/ram/texture.h>

namespace kengine {
	class TextureImporter
	{
	public:
		TextureImporter()
		{
		}

		~TextureImporter()
		{
		}

		static TexturePtr import(const string &filename);

	};

}