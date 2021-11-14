#pragma once
#include "../base/buffer.h"
#include "mmap.h"
namespace kengine {
    class IO {
    public:
        //static IO* instance() {
        //    return instance_;
        //}
        //static void set_instance(IO* ins) {
        //    instance_ = ins;
        //}
        virtual BufferPtr read_file(string_view file_name) = 0;
		virtual MapFilePtr mmap_file(string& file_name)
		{
            auto mmap = std::make_shared<MapFile>(file_name);
            
            return mmap;
		}
    //private:
    //    static IO* instance_;
    };
}
