#pragma once
namespace kengine {
	class FontBitmapCache
	{
	public:
		FontBitmapCache()
		{
		}

		~FontBitmapCache()
		{
		}
		int max_width;
		int max_height;
		int num;
		TexturePtr texture;

	};

}