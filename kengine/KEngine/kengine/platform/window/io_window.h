#pragma once
#include "../../core/io/kengine_io.h"
#include <fstream>
namespace kengine {
	class IOWindow :public IO
	{
	public:
		//virtual ~IOWindow() = default;
		BufferPtr read_file(string_view file_name) override {
			auto buffer = std::make_shared<Buffer>();
			std::ifstream file_stream;
			file_stream.open(file_name.data(), std::ios::binary);      // open input file  
			file_stream.seekg(0, std::ios::end);    // go to the end  
			const int length = static_cast<int>( file_stream.tellg() );           // report location (this is the length)  
			file_stream.seekg(0, std::ios::beg);    // go back to the beginning  
			buffer->malloc(length + 1);
			file_stream.read(buffer->data, length);       // read the whole file into the buffer  
			buffer->data[length] = '\0';
			file_stream.close();                    // close file handle  
			return buffer;
		}
	};
}
