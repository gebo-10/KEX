#pragma once

#include "kengine/resource/gpu/gpu_shader.h"
#include"resource.h"
namespace kengine {
    class Shader : public Resource{
    public:
        GPUShaderPtr gpu_shader;
        string_view vert_source;
        string_view frag_source;

        void gpucache() {
            //if gpu_shader ~= nullptr  return
            gpu_shader = std::make_shared<GPUShader>(vert_source, frag_source);
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
