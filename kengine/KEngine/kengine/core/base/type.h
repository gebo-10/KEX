#pragma once
#include<string>
#include<string_view>
#include<cstdint>
#include<vector>
#include<map>
#include<iostream>
#include<memory>
#include<any>
#include<stack>
#include<functional>
#include<cassert>

#define makes(T, ...) std::make_shared <T>(__VA_ARGS__)
#define makeu(T, ...) std::make_unique <T>(__VA_ARGS__)

#define REG(NAME) \
	typedef NAME * NAME##Ptr; \
    typedef std::shared_ptr<NAME> NAME##SPtr; \
    typedef std::unique_ptr<NAME> NAME##UPtr; \
    typedef std::weak_ptr<NAME> NAME##WPtr; \

namespace kengine {
    typedef char byte;
    typedef unsigned char ubyte;
    typedef std::string string;
    typedef std::string_view string_view;
    typedef int8_t int8;
    typedef uint8_t uint8;
    typedef int16_t int16;
    typedef uint16_t uint16;
    typedef int32_t int32;
    typedef uint32_t uint32;
    typedef uint32_t uint;
    typedef uint64_t uint64;
    //typedef std::string URL;
    typedef unsigned int GPUID;
    typedef uint32 PathID;
    typedef uint32 UID;
    typedef std::any any;
    typedef uint32 Name;
    template <typename T> using shared_ptr = std::shared_ptr<T>;
    template <typename T> using weak_ptr = std::weak_ptr<T>;
}