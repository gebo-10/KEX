#pragma once
#include"type.h"
#include"buffer.h"
#include"object_alloc.h"
namespace kengine {
	class LinkObjectAlloc
	{
	private:
		int object_size;
		int alloc_count;
		int segment_size;
		shared_ptr<ObjectAlloc> first;
	public:
		LinkObjectAlloc(int object_size_,int alloc_count_):
			object_size(object_size_), 
			alloc_count(alloc_count_),
			segment_size(object_size_* alloc_count_)
		{
			first = std::make_shared<ObjectAlloc>(object_size_, alloc_count_);
		}

		~LinkObjectAlloc()
		{
		}

		template<typename T>
		T* alloc() {
			void* res = nullptr;
			visit([&](shared_ptr<ObjectAlloc> seg)->bool {
				auto obj= seg->alloc(p);
				if (obj == nullptr) {
					if (seg->next == nullptr && obj == nullptr) {
						expend();
					}
					return false;
				}
				else {
					res = obj;
					return true;
				}
			});
			return (T*)res;
		}

		void free(byte* p) {
			visit([&](shared_ptr<ObjectAlloc> seg)->bool {
				return seg->free(p);
			});
		}

		void expend() {
			visit([&](shared_ptr<ObjectAlloc> seg)->bool {
				if (seg->get_next() == nullptr) {
					seg->get_next() = std::make_shared<ObjectAlloc>(object_size, alloc_count);
					return true;
				}
				else {
					return false;
				}
			});
		}

		void visit(std::function< bool(shared_ptr<ObjectAlloc>) > visitor) {
			auto current = first;
			while (true)
			{
				if (current == nullptr) {
					return;
				}
				if (visitor(current)) {
					break;
				}
				else {
					current = current->get_next();
				}
			}
		}
	};
}