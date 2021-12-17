#pragma once
#include "kengine/resource/gpu/gpu_shader.h"
#include"resource.h"
#include "uniform.h"
namespace kengine {
    class Shader : public Resource{
    public:
        GPUShaderPtr gpu_shader;
        string vert_source; //todo change stringptr
        string frag_source;
        string compute_source;

        std::vector<Uniform> uniforms;

        Shader() = default;
        Shader(string & vert, string& frag) {
            vert_source = std::move(vert);
            frag_source = std::move(frag);
        }
        Shader(string& compute) {
            compute_source = std::move(compute);
        }
        void gpucache() {
            if (dirty) uncache();
            if (gpu_shader != nullptr) return;
            gpu_shader = std::make_shared<GPUShader>(vert_source, frag_source, compute_source);
            dirty = false;
        }
        void uncache() {
            gpu_shader = nullptr;
        }

        void bind() {
            if (gpu_shader == nullptr) {
                gpucache();
            }
            gpu_shader->bind();
        }

        void unbind() {
            gpu_shader->unbind();
        }

        void sync() {
            for (auto& uniform : uniforms) {
                uniform.sync();
            }
        }

        void set_uniform(const Uniform & uniform) {
            auto ptr = get_uniform(uniform.location);
            if (ptr != nullptr) {
                ptr->set(uniform.buffer->data);
            }
            else {
                uniforms.push_back( Uniform(uniform) );
            }
        }

        Uniform* get_uniform(int location) {
            for (auto& uniform : uniforms) {
                if (uniform.location == location) {
                    return &uniform;
                }
            }
            return nullptr;
        }

        
    };
    typedef shared_ptr<Shader> ShaderPtr;
}
