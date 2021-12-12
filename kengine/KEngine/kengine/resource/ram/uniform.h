#pragma once
#include "resource.h"
#include "kengine/resource/ram/shader.h"
#include <kengine/core/math/kmath.h>
#include <kengine/resource/ram/texture.h>
//namespace kengine {
//	class Uniform {
//    public:
//       bool dirt=true;
//       ShaderDataType data_type;
//       int location=-1;
//       std::any value;
//
//       void set(std::any a) {
//           if (compare(a)) return;
//           value = a;
//           dirt = true;
//       }
//
//       void sync() {
//           if (!dirt) return;
//           dirt = false;
//           //if (location == -1) {
//           //    auto str = Env.name_service.get_str(name);
//           //    uint program = shader->gpu_shader->program_id;
//           //    location = glGetUniformLocation(program, str.c_str());
//           //}
//           switch (data_type)
//           {
//           case ShaderDataType::INT:
//               glUniform1i(location, std::any_cast<int>(value));
//               break;
//           case ShaderDataType::UINT:
//               glUniform1ui(location, std::any_cast<uint32>(value));
//               break;
//           case ShaderDataType::FLOAT:
//               glUniform1f(location, std::any_cast<float>(value));
//               break;
//           case ShaderDataType::VEC2: {
//               auto v2 = std::any_cast<vec2>(value);
//               glUniform2f(location, v2.x, v2.y);
//               break;
//           }
//           case ShaderDataType::VEC3: {
//               auto v3 = std::any_cast<vec3>(value);
//               glUniform3f(location, v3.x, v3.y, v3.z);
//               break;
//           }
//           case ShaderDataType::VEC4: {
//               auto v4 = std::any_cast<vec4>(value);
//               //glUniform4f(location, v4.x, v4.y, v4.z, v4.w);
//               glUniform1fv(location, 4, glm::value_ptr(v4));
//               break;
//           }
//           case ShaderDataType::MAT3:
//               mat3 m3 = std::any_cast<mat3>(value);
//               //glUniformMatrix4fv(location, 1, false, &m3[0][0]);
//               break;
//           case ShaderDataType::MAT4: {
//               mat4 m4 = std::any_cast<mat4>(value);
//               glUniformMatrix4fv(location, 1, false, &m4[0][0]);
//               break;
//           }
//           case ShaderDataType::SAMPLE2D: {
//               auto data = std::any_cast<TextureUniform>(value);
//               data.texture->bind(data.bind_point);
//               //glUniform1i(location, data.bind_point);
//               break;
//           }
//           case ShaderDataType::Color: {
//               Color c= std::any_cast<Color>(value);
//               glUniform4f(location, c.r, c.g, c.b, c.a);
//               break;
//           }
//           default:
//               break;
//           }
//       }
//   
//       bool compare(std::any& other) {
//           switch (data_type)
//           {
//           case ShaderDataType::INT:
//               return std::any_cast<int>(value) == std::any_cast<int>(other);
//               break;
//           case ShaderDataType::UINT:
//               return std::any_cast<uint32>(value) == std::any_cast<uint32>(other);
//               break;
//           case ShaderDataType::FLOAT:
//               return std::any_cast<float>(value) == std::any_cast<float>(other);
//               break;
//           case ShaderDataType::VEC2: {
//               return std::any_cast<vec2>(value) == std::any_cast<vec2>(other);
//               break;
//           }
//           case ShaderDataType::VEC3: {
//               return std::any_cast<vec3>(value) == std::any_cast<vec3>(other);
//               break;
//           }
//           case ShaderDataType::VEC4: {
//               return std::any_cast<vec4>(value) == std::any_cast<vec4>(other);
//               break;
//           }
//           case ShaderDataType::MAT3:
//               return std::any_cast<mat3>(value) == std::any_cast<mat3>(other);
//               break;
//           case ShaderDataType::MAT4: {
//               return std::any_cast<mat4>(value) == std::any_cast<mat4>(other);
//               break;
//           }
//           case ShaderDataType::SAMPLE2D: {
//               return std::any_cast<TextureUniform>(value) == std::any_cast<TextureUniform>(other);
//               break;
//           }
//           case ShaderDataType::Color: {
//               return std::any_cast<Color>(value) == std::any_cast<Color>(other);
//           }
//           default:
//               error("data_type error");
//               break;
//           }
//       }
//   };
//}

namespace kengine {   
    struct Uniform {
        bool dirty = false;
        GPUType type;
        int location = -1;
        BufferPtr buffer;
        Uniform() = delete;
        Uniform(int location, GPUType type, int count):type(type),location(location) {
            int value_size = TypeInfo::gpu_type_size(type) * count;
            buffer = std::make_shared<Buffer>(value_size);
        }

        Uniform(int location, ShaderDataType shader_data_type, int count=1) :location(location) {
            auto info = TypeInfo::shader_data_type_info(shader_data_type);
            type = info.gpu_type;
            int value_size = info.size* count;
            buffer = std::make_shared<Buffer>(value_size);
        }

        void set(void* value) {
            if (memcmp(buffer->data, value, buffer->size) == 0) return;
            std::memcpy(buffer->data, value, buffer->size);
            dirty = true;
        }

        template<typename T>
        void set(T& value) {
            set(glm::value_ptr(value));
        }

        void set(Color& value) {set(&value); }
        void set(float& value) {set(&value);}
        void set(int& value) {set(&value);}
        void set(uint& value) {set(&value);}

        void sync() {
            if (!dirty) return;
            dirty = false;
            int count = buffer->size/TypeInfo::gpu_type_size(type);
            switch (type)
            {
            case kengine::GPUType::INT:
                glUniform1iv(location, count, (GLint*)buffer->data);
                break;
            case kengine::GPUType::UNSIGNED_INT:
                glUniform1uiv(location, count,(GLuint *) buffer->data);
                break;
            case kengine::GPUType::FLOAT:{
                float *f= (GLfloat*)buffer->data;
                if (count == 4) {
                    //glUniform4f(location, f[0], f[1], f[2], f[3]);
                    glUniform4fv(location, 1, f);
                    //glUniform1fv(location, 4,f);
                }
                //glUniform1fv(location, count, (GLfloat*)buffer->data);
                break;
            }
            default:
                break;
            }
        }
    };
}



