#pragma once
#include "type.h"
#include <stdlib.h>
namespace kengine {
    class Buffer {
    public:
        bool malloced;
        byte* data;
        uint32 size;
        Buffer() :malloced(false),data(nullptr), size(0) {}
        Buffer(void * ptr, uint32 size_, bool need_free=false) :malloced(need_free),data( (byte*)ptr ), size(size_) {}
        Buffer(uint32 malloc_size):malloced(false),data(nullptr), size(0)
        {
            malloc(malloc_size);
        }
        ~Buffer()
        {
            free();
        }

        void malloc(uint32 malloc_size) {
            free();
            data = (byte*)std::malloc(malloc_size);
            size = malloc_size;
            malloced=true;
        }
        void free() {
            if (!malloced) return;
            std::free((void*)data);
            data = nullptr;
            size = 0;
            malloced=false;
        }

        shared_ptr<Buffer> view(uint32 offset,uint32 size_) {
            return std::make_shared<Buffer>(data + offset, size_);
        }

    };
    typedef  shared_ptr<Buffer> BufferPtr;
}
