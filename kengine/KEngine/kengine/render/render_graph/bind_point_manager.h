#pragma once
#include <kengine/resource/gpu/gpu_buffer.h>
#include <kengine/resource/gpu/gpu_object.h>
#include <kengine/resource/gpu/gpu_texture.h>
namespace kengine {
	enum class BindPointType
	{
		VAO,
		Texture,
		SSBO,
		UBO,
		MAX,
	};

	struct TextureUnit {
		GPUID texture_2d = 0;
		GPUID texture_cube_map = 0;
		GPUID texture_2d_array = 0;
		GPUID texture_3d = 0;
		GPUID texture_2d_multisample = 0;
	};

	class BindPointManager
	{
	public:
		GPUID shader_bind_point = 0;
		GPUID vao_bind_point=0;
		GPUID ubo_bind_point[32] = { 0 };
		GPUID ssbo_bind_point[32] = { 0 };
		TextureUnit texture_bind_point[32];
		BindPointManager(){}

		~BindPointManager(){}

		void bind_shader(ShaderPtr shader) {
			auto id = shader->gpu_shader->program_id;
			if (id == shader_bind_point) return;
			shader_bind_point = id;
			shader->bind();
		}

		void bind_vao(GPUObjectPtr object) {
			auto id = object->gpu_id;
			if (id == vao_bind_point) return;
			vao_bind_point = id;
			object->bind();
		}

		void bind_ubo(GPUBufferPtr buffer,int point) {
			auto id = buffer->gpu_id;
			if (id == ubo_bind_point[point]) return;
			ubo_bind_point[point] = id;
			buffer->bind_to_point(point);
		}

		void bind_ssbo(GPUBufferPtr buffer, int point) {
			auto id = buffer->gpu_id;
			if (id == ssbo_bind_point[point]) return;
			ssbo_bind_point[point] = id;
			buffer->bind_to_point(point);
		}

		void bind_texture(GPUTexturePtr texture, int point) {
			auto id = texture->gpu_id;
			switch (texture->m_desc.type)
			{
			case kengine::TextureType::TEXTURE_2D:{
				GPUID& old = texture_bind_point[point].texture_2d;
				if (id == old) {
					return;
				}
				else {
					old = id;
					texture->bind(id);
				}
				break;
			}
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
	};

}