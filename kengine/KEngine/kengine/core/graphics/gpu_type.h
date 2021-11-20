#pragma once
//#include <stdexcept>
//#include<map>
#include "../base/base.h"
namespace kengine{
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
    enum class GPUDataType {
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
    };
    struct GPUDataTypeInfo
    {
        GPUDataType type;
        int num;
        int size;
        //GPUDataTypeInfo() {}
        //GPUDataTypeInfo(GPUDataType data_type, int data_num, int data_size) :type(data_type), num(data_num), size(data_size) {}
    };
    //extern std::map < GPUDataType, GPUDataTypeInfo > gpu_data_type_info;

    enum class Face {
        FRONT,
        BACK,
        FRONT_AND_BACK,
    };
}