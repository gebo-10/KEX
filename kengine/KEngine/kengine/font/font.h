#pragma once
#include <ft2build.h>
#include <freetype/ftoutln.h>
#include <freetype/freetype.h>  
#include <freetype/ftglyph.h>  
#include <freetype/ftoutln.h>  
#include <freetype/fttrigon.h> 
#include FT_FREETYPE_H

#include<kengine/core/base/base.h>
#include <kengine/resource/ram/texture.h>
namespace kengine {
	class Font {
	public:
		FT_Library	library;
		FT_Face		face;
		FT_Error	error;

		int   size;

		Font() {
			Init();
			SetFont("");
			SetFontSize(100);
		}
		~Font(){}
		bool Init() {
			error = FT_Init_FreeType(&library);
			return true;
		}
		void SetFont(const char* font_file) {
			error = FT_New_Face(library, "main\\font\\msyh.ttc", 0, &face);
		}
		void SetFontSize(int size) {
			error = FT_Set_Char_Size(face, size * 64, size * 64, 96, 96);
		}
		TexturePtr GetStrTexture(string str) {
			uint32 charIdx = FT_Get_Char_Index(face, L'¹þ');

			// 5. ¼ÓÔØ×Ö·ûÍ¼Ïñ
			FT_Load_Glyph(face, charIdx, FT_LOAD_DEFAULT);
			
			//int width = 100;
			//int height = 100;
			//Color* tmp = new Color[width * height];
			//for (int i = 0; i < height; i++)
			//{
			//	for (int j = 0; j < width; j++)
			//	{
			//		int index = i * width + j;
			//		tmp[index].r = i;
			//		tmp[index].g = j;
			//		tmp[index].b = 100;
			//		tmp[index].a = 255;
			//	}
			//}
			//ptr->InitFromMem( (void * )tmp, width,  height);

			FT_Glyph glyph;
			FT_Get_Glyph(face->glyph, &glyph);

			//Convert the glyph to a bitmap.
			FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
			FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

			//This reference will make accessing the bitmap easier
			FT_Bitmap& bitmap = bitmap_glyph->bitmap;

			auto buf = std::make_shared<Buffer>(bitmap.buffer, bitmap.width * bitmap.rows);
			TextureDesc desc;
			desc.width = bitmap.width;
			desc.height = bitmap.rows;
			desc.data_format = TextureDataFormat::RED;
			desc.internal_format = TextureInternalFormat::R8;
			desc.alignment = 1;
			TexturePtr ptr = std::make_shared<Texture>(desc);
			ptr->add_data(buf);

			//char* pBuf = new char[width * height * 4];
			//for (int j = 0; j < height; j++)
			//{
			//	for (int i = 0; i < width; i++)
			//	{
			//		unsigned char _vl = (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
			//		pBuf[(4 * i + (height - j - 1) * width * 4)] = _vl;
			//		pBuf[(4 * i + (height - j - 1) * width * 4) + 1] = 0xFF;
			//		pBuf[(4 * i + (height - j - 1) * width * 4) + 2] = 0xFF;
			//		pBuf[(4 * i + (height - j - 1) * width * 4) + 3] = 0xFF;
			//	}
			//}

			//ptr->InitFromMem((void*)pBuf, width, width);
			return ptr;
		}

	};
}