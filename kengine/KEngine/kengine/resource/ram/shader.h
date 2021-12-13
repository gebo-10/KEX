#pragma once
#include "kengine/resource/gpu/gpu_shader.h"
#include"resource.h"
namespace kengine {
    class Shader : public Resource{
    public:
        GPUShaderPtr gpu_shader;
        string vert_source; //todo change stringptr
        string frag_source;
        string compute_source;
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
    };
    typedef shared_ptr<Shader> ShaderPtr;
}
