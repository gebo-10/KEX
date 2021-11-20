#pragma once
//#include "../../core/graphics/graphics.h"
#include"resource.h"
namespace kengine {
	enum WarpMode
	{
		REPEAT,
		CLAMP,
		MIRROR,
	};

	enum FilterMode
	{
		POINT,
		BILINEAR,
		TRLINEAR,
	};
	class Texture : public Resource
	{
	public:
		//GPUImagePtr gpu_image;
		//int type = GL_TEXTURE_2D;
		int format;
		int width;
		int height;
		bool ReadWriteEnabled;

	};
	typedef shared_ptr<Texture> TexturePtr;
}