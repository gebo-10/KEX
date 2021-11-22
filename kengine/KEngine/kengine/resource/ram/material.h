#pragma once
#include "resource.h"
#include "kengine/resource/ram/shader.h"
#include <kengine/core/math/kmath.h>
#include <kengine/resource/ram/texture.h>
namespace kengine {
    struct Uniform {
        bool dirt=false;
        ShaderDataType data_type;
        int location=-1;
        std::any value;
        void set(std::any a) {
            if (compare(a)) return;
            value = a;
            dirt = true;
        }

        void sync(ShaderPtr shader) {
            if (!dirt) return;
            dirt = false;
            //if (location == -1) {
            //    auto str = Env.name_service.get_str(name);
            //    uint program = shader->gpu_shader->program_id;
            //    location = glGetUniformLocation(program, str.c_str());
            //}
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
    
        bool compare(std::any& other) {
            switch (data_type)
            {
            case ShaderDataType::INT:
                return std::any_cast<int>(value) == std::any_cast<int>(other);
                break;
            case ShaderDataType::UINT:
                return std::any_cast<uint32>(value) == std::any_cast<uint32>(other);
                break;
            case ShaderDataType::FLOAT:
                return std::any_cast<float>(value) == std::any_cast<float>(other);
                break;
            case ShaderDataType::VEC2: {
                return std::any_cast<vec2>(value) == std::any_cast<vec2>(other);
                break;
            }
            case ShaderDataType::VEC3: {
                return std::any_cast<vec3>(value) == std::any_cast<vec3>(other);
                break;
            }
            case ShaderDataType::VEC4: {
                return std::any_cast<vec4>(value) == std::any_cast<vec4>(other);
                break;
            }
            case ShaderDataType::MAT3:
                return std::any_cast<mat3>(value) == std::any_cast<mat3>(other);
                break;
            case ShaderDataType::MAT4: {
                return std::any_cast<mat4>(value) == std::any_cast<mat4>(other);
                break;
            }
            case ShaderDataType::SAMPLE2D: {
                return std::any_cast<int>(value) == std::any_cast<int>(other);
                break;
            }
            default:
                error("data_type error");
                break;
            }
        }
    };

    class Material : public Resource {
    public:
        ShaderPtr shader;
        std::vector<Uniform> uniforms;
        //std::unordered_map<std::string, Uniform> uniforms;
        Material(ShaderPtr pshader)
        {
            shader = pshader;
        }

        ~Material() {
            unbind();
        }

        void bind() {
            sync_uniform();
        }

        void unbind() {
            shader->unbind();
        }

        void sync_uniform() {
            shader->bind();
            for (Uniform& uniform : uniforms) {
                uniform.sync(shader);
            }
        }

        void set_shader(ShaderPtr  shader) {
            this->shader = shader;
        }

        void set_model_matrix(Matrix M) {
            //int location = glGetUniformLocation(shader->gpu_id, "M");
            glUniformMatrix4fv(0, 1, false, &M[0][0]);
        }

        bool set_uniform(Name name, std::any value) {
            auto uniform = find_uniform(name);
            if (uniform != nullptr) {
                uniform->set(value);
                return true;
            }
            return false;
        }

        void add_uniform(int location, ShaderDataType data_type,std::any value) {
            uniforms.push_back(Uniform{ true,data_type, location,value });
        }

        Uniform* find_uniform(int location) {
            for (Uniform& uniform : uniforms) {
                if (uniform.location == location) {
                    return &uniform;
                }
            }
            return nullptr;
        }
    };
    typedef shared_ptr<Material> MaterialPtr;
}
