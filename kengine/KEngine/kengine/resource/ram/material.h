#pragma once
#include "resource.h"
#include "kengine/resource/ram/shader.h"
#include <kengine/core/math/kmath.h>
#include <kengine/resource/ram/texture.h>
namespace kengine {
    class Uniform {
        bool dirt;
        int location;
        ShaderDataType data_type;
        std::any data;
    };

    class Material : public Resource {
    public:
        ShaderPtr shader;
        std::vector<Uniform> uniforms;

        Material(ShaderPtr pshader)
        {
            shader = pshader;
        }

        ~Material() {
            unbind();
            uncache();
        }

        void gpucache() {
           
        }
        void uncache() {

        }

        void bind() {
            
        }

        void unbind() {

        }

        void set_shader(ShaderPtr  shader) {
            this->shader = shader;
        }

        void set_model_matrix(Matrix M) {
            //int location = glGetUniformLocation(shader->gpu_id, "M");
            //glUniformMatrix4fv(location, 1, false, &M[0][0]);
        }

        void set_uniform(int location, ShaderDataType data_type, std::any value) {
            //shader->bind();
            switch (data_type)
            {
            case ShaderDataType::INT:
                glUniform1i(location, std::any_cast<int>(value));
                break;
            case ShaderDataType::UINT:
                glUniform1ui(location, std::any_cast<uint32>(value));
                break;
            case ShaderDataType::FLOAT:
                glUniform1f(location, std::any_cast<float>(value));
                break;
            case ShaderDataType::VEC2: {
                auto v2 = std::any_cast<vec2>(value);
                glUniform2f(location, v2.x, v2.y);
                break;
            }
            case ShaderDataType::VEC3: {
                auto v3 = std::any_cast<vec3>(value);
                glUniform3f(location, v3.x, v3.y, v3.z);
                break;
            }
            case ShaderDataType::VEC4: {
                auto v4 = std::any_cast<vec4>(value);
                glUniform4f(location, v4.x, v4.y, v4.z, v4.w);
                break;
            }
            case ShaderDataType::MAT3:
                mat3 m3 = std::any_cast<mat3>(value);
                glUniformMatrix4fv(location, 1, false, &m3[0][0]);
                break;
            case ShaderDataType::MAT4: {
                mat4 m4 = std::any_cast<mat4>(value);
                glUniformMatrix4fv(location, 1, false, &m4[0][0]);
                break;
            }
            case ShaderDataType::SAMPLE2D: {
                //auto tex = std::any_cast<TexturePtr>(value);
                //int texture_index = std::atoi(key.data() + 7);
                //tex->bind(texture_index);
                //glUniform1i(location, texture_index);
                break;
            }
            default:
                break;
            }
        }
    };
    typedef shared_ptr<Material> MaterialPtr;
}
