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
        //bool operator==(const TextureUniform& other) {
        //    return bind_point == other.bind_point && texture == other.texture;
        //}
    };

    struct BufferUniform {
        int bind_point;
        GPUBufferPtr gpu_buffer;
    };

    class Material : public Resource {
    public:
        ShaderPtr shader;
        std::vector<Uniform> uniforms;
        std::vector<TextureUniform> texture_uniforms;
        std::vector<BufferUniform> buffer_uniforms;
        Material(ShaderPtr pshader)
        {
            shader = pshader;
        }

        ~Material() {
            //unbind();
        }

        void bind() {
            shader->bind();
        }
        //void unbind() {
        //    shader->unbind();
        //}

        void attach_uniform(BindPointManager &bind_point_manager) {
            //bind_point_manager.bind_shader(shader);
            for (Uniform& uniform : uniforms) {
                uniform.sync();
            }
            for (auto & texture_uniform : texture_uniforms) {
                texture_uniform.texture->gpucache();
                bind_point_manager.bind_texture(texture_uniform.texture->gpu_texture, texture_uniform.bind_point);
            }

            for (auto& buffer_uniform : buffer_uniforms) {
                if (buffer_uniform.gpu_buffer->type == (int)GPUBufferType::UNIFORM_BUFFER) {
                    bind_point_manager.bind_ubo(buffer_uniform.gpu_buffer, buffer_uniform.bind_point);
                }
                else if (buffer_uniform.gpu_buffer->type == (int)GPUBufferType::SHADER_STORAGE_BUFFER) {
                    bind_point_manager.bind_ssbo(buffer_uniform.gpu_buffer, buffer_uniform.bind_point);
                }
            }
        }

        void set_shader(ShaderPtr  shader) {
            this->shader = shader;
        }

        void set_model_matrix(Matrix M) {
            //int location = glGetUniformLocation(shader->gpu_id, "M");
            //glUniformMatrix4fv(0, 1, false,glm::value_ptr(M));
            //glUniform1fv(0,16,(float *) &M);
            set_uniform(0, M);
        }

        template <typename T>
        bool set_uniform(Name name, T value) {
            auto uniform = get_uniform(name);
            if (uniform != nullptr) {
                uniform->set(value);
                return true;
            }
            return false;
        }

        bool set_uniform(Name name, void * value) {
            auto uniform = get_uniform(name);
            if (uniform != nullptr) {
                uniform->set(value);
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
            for (auto & uniform : uniforms) {
                if (uniform.location == location) {
                    return &uniform;
                }
            }
            return nullptr;
        }


        void add_texture(int bind_point,TexturePtr texture ) {
            texture_uniforms.push_back(TextureUniform{ bind_point , texture});
        }

        void add_buffer(int bind_point, GPUBufferPtr buffer) {
            buffer_uniforms.push_back(BufferUniform{ bind_point , buffer });
        }
    };
    typedef shared_ptr<Material> MaterialPtr;
}
