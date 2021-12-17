#pragma once
#include"type.h"
#include"buffer.h"
namespace kengine {
	class ObjectAlloc {
	private:
		BufferPtr buffer = nullptr;
		shared_ptr<ObjectAlloc> next = nullptr;
		byte* table = nullptr;
		int object_size = 0;
		int alloc_count = 0;

	public:
		ObjectAlloc(int object_size_, int alloc_count_) :object_size(object_size_), alloc_count(alloc_count_) {
			buffer = std::make_shared<Buffer>(alloc_count * object_size_);
			table = new byte[alloc_count_];
		}
		~ObjectAlloc() {
			delete table;
		}
		inline shared_ptr<ObjectAlloc> get_next() {
			return next;
		}

		byte* alloc() {
			for (size_t i = 0; i < alloc_count; i++)
			{
				if (table[i] != 0) {
					return buffer->data + (i * object_size);
				}
			}
			return nullptr;
		}

		bool free(byte* p) {
			byte* base = buffer->data;
			if (p > base && p < base + buffer->size) {
				auto size = p - base;
				auto index = size / object_size;
				table[index] = 0;
				return true;
			}
			else {
				return false;
			}
		}
	};
}