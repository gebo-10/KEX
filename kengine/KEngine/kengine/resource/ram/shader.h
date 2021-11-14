#pragma once
#include "../../core/graphics/graphics.h"
#include "kengine/resource/gpu/gpu_shader.h"
#include"resource.h"
namespace kengine {
    class Shader : public Resource{
    public:
        GPUShaderPtr gpu_shader;
        string_view vert_source;
        string_view frag_source;

        void cache_to_gpu() {
            gpu_shader = std::make_shared<GPUShader>(vert_source, frag_source);
        }
    };
    typedef shared_ptr<Shader> ShaderPtr;
}
