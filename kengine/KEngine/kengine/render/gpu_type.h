#pragma once
//#include <stdexcept>
//#include<map>
#include <kengine/core/base/base.h>
#include "graphics_api.h"
namespace kengine{
    enum class GPUType {
        BYTE = GL_BYTE,
        UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
        SHORT = GL_SHORT,
        UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
        INT = GL_INT,
        UNSIGNED_INT = GL_UNSIGNED_INT,
        FLOAT = GL_FLOAT,
        HALF_FLOAT = GL_HALF_FLOAT,
        FIXED = GL_FIXED,
        INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
        UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
    };

    enum class PrimitiveType {
        POINTS = GL_POINTS,
        LINES = GL_LINES,
        LINE_LOOP= GL_LINE_LOOP,
        LINE_STRIP = GL_LINE_STRIP,
        TRIANGLES = GL_TRIANGLES,
        TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
        QUADS = GL_QUADS,
        QUAD_STRIP = GL_QUAD_STRIP,
        PRIMITIVE_MAX,
    };
    enum class ShaderDataType {
        INT,
        UINT,
        FLOAT,
        VEC2,
        VEC3,
        VEC4,
        MAT2,
        MAT3,
        MAT4,
        Color,
        MAX,
    };
    struct ShaderDataTypeInfo
    {
        GPUType gpu_type;
        int size;
    };
    //extern std::map < GPUDataType, GPUDataTypeInfo > gpu_data_type_info;

    class TypeInfo {
    public:
        static int gpu_type_size(GPUType type) {
            switch (type)
            {
            case kengine::GPUType::BYTE: return sizeof(byte);
            case kengine::GPUType::UNSIGNED_BYTE: return sizeof(ubyte);
            case kengine::GPUType::SHORT: return sizeof(int16);
            case kengine::GPUType::UNSIGNED_SHORT: return sizeof(uint16);
            case kengine::GPUType::INT: return sizeof(int32);
            case kengine::GPUType::UNSIGNED_INT:return sizeof(uint32);
            case kengine::GPUType::FLOAT:return sizeof(float);
            case kengine::GPUType::HALF_FLOAT:return sizeof(int16);
            case kengine::GPUType::FIXED:return sizeof(uint32);
            case kengine::GPUType::INT_2_10_10_10_REV:return sizeof(uint32);
            case kengine::GPUType::UNSIGNED_INT_2_10_10_10_REV:return sizeof(uint32);
            default: return 0;
            }
        }
    
        static ShaderDataTypeInfo shader_data_type_info(ShaderDataType type) {
            switch (type)
            {
            case kengine::ShaderDataType::INT:
                return { GPUType::INT ,sizeof(int) };
            case kengine::ShaderDataType::UINT:
                return { GPUType::UNSIGNED_INT ,sizeof(int) };
            case kengine::ShaderDataType::FLOAT:
                return { GPUType::FLOAT ,sizeof(float) };
            case kengine::ShaderDataType::VEC2:
                return { GPUType::FLOAT ,sizeof(float)*2 };
            case kengine::ShaderDataType::VEC3:
                return { GPUType::FLOAT ,sizeof(float) * 3 };
            case kengine::ShaderDataType::VEC4:
                return { GPUType::FLOAT ,sizeof(float) * 4 };
            case kengine::ShaderDataType::MAT2:
                return { GPUType::FLOAT ,sizeof(float) * 4 };
            case kengine::ShaderDataType::MAT3:
                return { GPUType::FLOAT ,sizeof(float) * 9 };
            case kengine::ShaderDataType::MAT4:
                return { GPUType::FLOAT ,sizeof(float) * 16 };
            case kengine::ShaderDataType::Color:
                return { GPUType::FLOAT ,sizeof(float) * 4 };
            default:
                error("TypeInfo.shader_data_type_info: UnKnow type");
                break;
            }
        }
    };
}