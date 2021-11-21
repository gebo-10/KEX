#pragma once
#include "gpu_resource.h"
#include "gpu_buffer.h"
namespace kengine {
	//https://blog.csdn.net/afei__/article/details/96158388?spm=1001.2101.3001.6650.3&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-3.no_search_link&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-3.no_search_link
	//https://www.khronos.org/registry/OpenGL-Refpages/es3.0/html/glTexStorage2D.xhtml
	enum class TextureDataFormat
	{
		ALPHA,
		RGBA, 
		RGB,
		RG,
		RED, 
		RGBA_INTEGER,
		RGB_INTEGER,
		RG_INTEGER,
		RED_INTEGER,
		DEPTH_COMPONENT,
		DEPTH_STENCIL,
		LUMINANCE_ALPHA, 
		LUMINANCE
	};
	enum class TextureDataType {
		BYTE,
		UNSIGNED_BYTE,
		SHORT,
		UNSIGNED_SHORT,
		INT,
		UNSIGNED_INT,
		FLOAT,
		HALF_FLOAT,
		UNSIGNED_SHORT_4_4_4_4,
		UNSIGNED_SHORT_5_5_5_1,
		UNSIGNED_SHORT_5_6_5,
		UNSIGNED_INT_2_10_10_10_REV,
		UNSIGNED_INT_24_8,
		UNSIGNED_INT_10F_11F_11F_REV,
		UNSIGNED_INT_5_9_9_9_REV,
		FLOAT_32_UNSIGNED_INT_24_8_REV
	};

	enum class TextureInternalFormat {
		R8, R8I, R8UI, R8_SNORM, R16I, R16UI, R16F, R32I,
		R32UI, R32F, RG8, RG8I, RG8UI, RG8_SNORM, RG16I, RG16UI, RG16F,
		RG32I, RG32UI, RG32F, RGB, RGB5_A1, RGB565, RGB8, RGB8I,
		RGB8UI, RGB8_SNORM, RGB9_E5, RGB10_A2, RGB10_A2UI, RGB16I,
		RGB16UI, RGB16F, RGB32I, RGB32UI, RGB32F, SRGB8, RGBA, RGBA4,
		RGBA8, RGBA8I, RGBA8UI, RGBA8_SNORM, RGBA16I, RGBA16UI,
		RGBA16F, RGBA32I, RGBA32UI, RGBA32F, SRGB8_ALPHA8,
		R11F_G11F_B10F, DEPTH_COMPONENT16, DEPTH_COMPONENT24,
		DEPTH_COMPONENT32F, DEPTH24_STENCIL8, DEPTH32F_STENCIL8,
		LUMINANCE_ALPHA, LUMINANCE, ALPHA,

		COMPRESSED_RGBA8_ETC2_EAC = GL_COMPRESSED_RGBA8_ETC2_EAC,
		COMPRESSED_R11_EAC,
		COMPRESSED_SIGNED_R11_EAC,
		COMPRESSED_RG11_EAC,
		COMPRESSED_SIGNED_RG11_EAC,
		COMPRESSED_RGB8_ETC2,
		COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,
		COMPRESSED_SRGB8_ETC2,
		COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2,
		COMPRESSED_SRGB8_ALPHA8_ETC2_EAC
	};

	enum TextureWarpMode
	{
		REPEAT=GL_REPEAT,
		MIRRORED_REPEAT=GL_MIRRORED_REPEAT,
		CLAMP_TO_EDGE=GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
	};

	enum TextureFilterMode
	{
		POINT,
		LINEAR,
		BILINEAR,
		TRLINEAR,
	};

	enum class TextureType {
		TEXTURE_2D,
		TEXTURE_CUBE_MAP, 
		TEXTURE_2D_ARRAY,
		TEXTURE_3D,
		TEXTURE_2D_MULTISAMPLE,
	};
	
	enum class CubeMapFace {
		TEXTURE_CUBE_MAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		TEXTURE_CUBE_MAP_POSITIVE_Y,
		TEXTURE_CUBE_MAP_POSITIVE_Z,
		TEXTURE_CUBE_MAP_NEGATIVE_X,
		TEXTURE_CUBE_MAP_NEGATIVE_Y,
		TEXTURE_CUBE_MAP_NEGATIVE_Z,
	};
	//enum class CompressedTextureFormat {}

	struct TextureDesc {
		TextureType type = TextureType::TEXTURE_2D;
		TextureDataType data_type = TextureDataType::UNSIGNED_BYTE;
		TextureDataFormat data_format = TextureDataFormat::RGBA;
		TextureInternalFormat internal_format= TextureInternalFormat::RGBA;

		TextureFilterMode min_filter = TextureFilterMode::LINEAR;
		TextureFilterMode mag_filter = TextureFilterMode::LINEAR;
		
		TextureWarpMode s_warp = TextureWarpMode::CLAMP_TO_EDGE;
		TextureWarpMode r_warp = TextureWarpMode::CLAMP_TO_EDGE;
		TextureWarpMode t_warp = TextureWarpMode::CLAMP_TO_EDGE;

		bool compressed = false;
		int width=64;
		int height=64;
		int board = 0;
	};

	class GPUTexture
	{
	public:
		TextureDesc m_desc;
		GPUID gpu_id = -1;
		GPUTexture(const TextureDesc &desc, const std::vector<BufferPtr>& buffers) {
			m_desc = desc;
			glGenTextures(1, &gpu_id);
			glBindTexture((GLenum)desc.type, gpu_id);
			texture_data(desc, buffers);
			param(desc);
		}

		~GPUTexture() {
			glDeleteTextures(1, &gpu_id);
		}

		void update_data(const std::vector<BufferPtr>& buffers) {
			glBindTexture(GL_TEXTURE_2D, gpu_id);
			texture_data(m_desc, buffers);
		}

		void update_data(const TextureDesc& desc,const std::vector<BufferPtr>& buffers) {
			m_desc = desc;
			glBindTexture(GL_TEXTURE_2D, gpu_id);
			texture_data(desc, buffers);
		}
		
		void bind(int index) {
			//glEnable(GL_TEXTURE_2D);
			glActiveTexture(GL_TEXTURE0 + index);
			glBindTexture((GLenum)m_desc.type, gpu_id);
		}
		
		void unbind(void) {
			glBindTexture((GLenum)m_desc.type, 0);
		}

		void set_param(const TextureDesc& desc) {
			m_desc.min_filter = desc.min_filter;
			m_desc.mag_filter = desc.mag_filter;
			m_desc.s_warp = desc.s_warp;
			m_desc.r_warp = desc.r_warp;
			m_desc.t_warp = desc.t_warp;
			param(desc);
		}

	private:
		void texture_data(const TextureDesc& desc, const std::vector<BufferPtr>& buffers) {
			switch (desc.type)
			{
			case kengine::TextureType::TEXTURE_2D:
				if (desc.compressed) {
					glCompressedTexImage2D((GLenum)desc.type, 0, (GLenum)desc.internal_format, desc.width, desc.height, desc.board, buffers[0]->size, buffers[0]->data);
				}
				else {
					if(buffers.size()==0){
						glTexImage2D((GLenum)desc.type, 0, (GLenum)desc.internal_format, desc.width, desc.height, desc.board, (GLenum)desc.data_format, (GLenum)desc.data_type, nullptr);
					}else{
						glTexImage2D((GLenum)desc.type, 0, (GLenum)desc.internal_format, desc.width, desc.height, desc.board, (GLenum)desc.data_format, (GLenum)desc.data_type, buffers[0]->data);
					}
				}
				break;
			case kengine::TextureType::TEXTURE_CUBE_MAP:
				break;
			case kengine::TextureType::TEXTURE_2D_ARRAY:
				break;
			case kengine::TextureType::TEXTURE_3D:
				break;
			case kengine::TextureType::TEXTURE_2D_MULTISAMPLE:
				break;
			default:
				break;
			}
		}

		void param(const TextureDesc& desc) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)desc.min_filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)desc.mag_filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)desc.s_warp);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, (GLenum)desc.r_warp);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)desc.t_warp);
		}
	};
	typedef shared_ptr<GPUTexture> GPUTexturePtr;
}
