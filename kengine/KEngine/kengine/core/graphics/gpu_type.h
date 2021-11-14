#pragma once
//#include <stdexcept>
//#include<map>
#include "../base/base.h"
namespace kengine{
enum PrimitiveType {
    PRIMITIVE_POINTS,
    PRIMITIVE_LINES,
    PRIMITIVE_LINE_STRIP,
    PRIMITIVE_TRIANGLES,
    PRIMITIVE_TRIANGLE_STRIP,
    PRIMITIVE_MAX,
};
enum GPUDataType {
    GPU_BYTE,
    GPU_SHORT,
    GPU_USHORT,
    GPU_INT,
    GPU_UINT,
    GPU_INT64,
    GPU_UINT64,
    GPU_HALF,
    GPU_FLOAT,
    GPU_VEC2,
    GPU_VEC3,
    GPU_VEC4,
    GPU_MAT3,
    GPU_MAT4,
    GPU_SAMPLE2D,
};
//struct GPUDataTypeInfo
//{
//    int type;
//    int num;
//    int size;
//    GPUDataTypeInfo() {}
//    GPUDataTypeInfo(int data_type, int data_num, int data_size) :type(data_type), num(data_num), size(data_size) {}
//};
//extern std::map < GPUDataType, GPUDataTypeInfo > gpu_data_type_info;
}