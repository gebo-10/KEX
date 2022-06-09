#pragma once
#include "resource.h"
#include "kengine/resource/ram/shader.h"
#include <kengine/core/math/kmath.h>
#include <kengine/resource/ram/texture.h>
#include <kengine/render/render_graph/bind_point_manager.h>
#include "uniform.h"
namespace kengine {
    struct TextureUniform {
        int bind_point;
        TexturePtr texture;
    };

    struct BufferUniform {
        GPUBufferType type;
        int bind_point;
        GPUBufferPtr gpu_buffer;
    };

    class Material : public Resource {
    public:
        ShaderPtr shader;
        std::vector<Uniform> uniforms;
        std::vector<TextureUniform> texture_uniforms;//TODO 使用数组
        std::vector<BufferUniform> buffer_uniforms;
        Material(ShaderPtr pshader)
        {
            shader = pshader;
        }

        ~Material() {
            //unbind();
        }

        Material(const Material& o) {  // 拷贝构造函数
            this->shader = o.shader;
            this->uniforms.assign(o.uniforms.begin(), o.uniforms.end());
            this->texture_uniforms.assign(o.texture_uniforms.begin(), o.texture_uniforms.end());
            this->buffer_uniforms.assign(o.buffer_uniforms.begin(), o.buffer_uniforms.end());
        }

        void bind() {
            shader->bind();
        }
        //void unbind() {
        //    shader->unbind();
        //}
        void set_dirty() {
            for (auto& uniform : uniforms) {
                uniform.dirty = true;
            }
        }

        //void attach_uniform(BindPointManager &bind_point_manager) {
        //    //bind_point_manager.bind_shader(shader);
        //    for (Uniform& uniform : uniforms) {
        //        //uniform.sync();
        //        if (uniform.dirty) {
        //            uniform.dirty = false;
        //            shader->set_uniform(uniform);
        //        }
        //    }
        //    shader->sync();

        //    for (auto & texture_uniform : texture_uniforms) {
        //        texture_uniform.texture->gpucache();
        //        bind_point_manager.bind_texture(texture_uniform.texture->gpu_texture, texture_uniform.bind_point);
        //    }

        //    for (auto& buffer_uniform : buffer_uniforms) {
        //        if (buffer_uniform.gpu_buffer->type == (int)GPUBufferType::UNIFORM_BUFFER) {
        //            bind_point_manager.bind_ubo(buffer_uniform.gpu_buffer, buffer_uniform.bind_point);
        //        }
        //        else if (buffer_uniform.gpu_buffer->type == (int)GPUBufferType::SHADER_STORAGE_BUFFER) {
        //            bind_point_manager.bind_ssbo(buffer_uniform.gpu_buffer, buffer_uniform.bind_point);
        //        }
        //    }
        //}

        void attach_uniform() {
            shader->bind();
            for (Uniform& uniform : uniforms) {
                if (uniform.dirty) {
                    uniform.dirty = false;
                    shader->set_uniform(uniform);
                }
            }
            shader->sync();

            for (auto& texture_uniform : texture_uniforms) {
                texture_uniform.texture->gpucache();
                texture_uniform.texture->gpu_texture->bind(texture_uniform.bind_point);
            }

            for (auto& buffer_uniform : buffer_uniforms) {
                buffer_uniform.gpu_buffer->bind_to_point(buffer_uniform.bind_point, buffer_uniform.type);
            }
        }

        void set_shader(ShaderPtr  shader) {
            this->shader = shader;
        }

        void set_model_matrix(Matrix M) {
            //int location = glGetUniformLocation(shader->gpu_id, "M");
            //glUniformMatrix4fv(0, 1, false,glm::value_ptr(M));
            set_uniform(0, glm::value_ptr(M));
        }

        //template <typename T>
        //bool set_uniform(Name name, T value) {
        //    auto uniform = get_uniform(name);
        //    if (uniform != nullptr) {
        //        uniform->set(value);
        //        return true;
        //    }
        //    return false;
        //}

        bool set_uniform(Name name, void * value,int size=-1) {
            auto uniform = get_uniform(name);
            if (uniform != nullptr) {
                uniform->set(value, size);
                return true;
            }
            return false;
        }

        void add_uniform(int location, ShaderDataType data_type, void * value, int count = 1) {
            Uniform uniform(location, data_type, count);
            uniform.set(value);
            uniforms.push_back(std::move(uniform));
        }

        //template <typename T>
        //void add_uniform(int location, ShaderDataType data_type, T value, int count = 1) {
        //    Uniform uniform(location, data_type);
        //    uniform.set(value);
        //    uniforms.push_back(std::move(uniform));
        //}

        Uniform* get_uniform(int location) {
            for (auto& uniform : uniforms) {
                if (uniform.location == location) {
                    return &uniform;
                }
            }
            return nullptr;
        }

        void set_uniforms(std::vector<Uniform> &uniforms) {
            for (auto& uniform : uniforms) {
                set_uniform(uniform.location, uniform.buffer->data);
            }
        }

        void add_texture(int bind_point,TexturePtr texture ) {
            for (auto& uniform : texture_uniforms) {
                if (uniform.bind_point == bind_point) {
                    uniform.texture = texture;
                    return;
                }
            }
            texture_uniforms.push_back(TextureUniform{ bind_point , texture});
        }

        TexturePtr get_texture(int bind_point) {
			for (auto& uniform : texture_uniforms) {
				if (uniform.bind_point == bind_point) {
                    return uniform.texture;
				}
			}
            return nullptr;
        }

        void add_textures(std::vector<TextureUniform> &uniforms) {
            for (auto& uniform : uniforms) {
                add_texture(uniform.bind_point, uniform.texture);
            }
        }

        void add_buffer(GPUBufferType type, int bind_point, GPUBufferPtr buffer) {
            for (auto& uniform : buffer_uniforms) {
                if (uniform.bind_point == bind_point) {
                    uniform.gpu_buffer = buffer;
                    return;
                }
            }
            buffer_uniforms.push_back(BufferUniform{ type, bind_point , buffer });
        }

        void add_buffers(std::vector<BufferUniform>& uniforms) {
            for (auto& uniform : uniforms) {
                add_buffer(uniform.type, uniform.bind_point, uniform.gpu_buffer);
            }
        }
    };
    typedef shared_ptr<Material> MaterialPtr;
}
