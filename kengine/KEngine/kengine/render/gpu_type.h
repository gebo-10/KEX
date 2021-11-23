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
    };

    enum class PrimitiveType {
        POINTS,
        LINES,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_STRIP,
        QUADS,
        QUAD_STRIP,
        PRIMITIVE_MAX,
    };
    enum class ShaderDataType {
        INT,
        UINT,
        FLOAT,
        VEC2,
        VEC3,
        VEC4,
        RGB,
        RGBA,
        MAT3,
        MAT4,
        SAMPLE2D,
        Color,
    };
    struct ShaderDataTypeInfo
    {
        ShaderDataType type;
        int num;
        int size;
        //GPUDataTypeInfo() {}
        //GPUDataTypeInfo(GPUDataType data_type, int data_num, int data_size) :type(data_type), num(data_num), size(data_size) {}
    };
    //extern std::map < GPUDataType, GPUDataTypeInfo > gpu_data_type_info;

    
}