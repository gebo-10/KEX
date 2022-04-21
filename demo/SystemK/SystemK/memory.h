#pragma once
#include <unordered_map>
namespace ksystem {
	struct MemeryItem
	{
		int type;
		short shared_count;
		short weak_count;
	};
	class Memory
	{
	public:
		std::unordered_map<void*, MemeryItem> record;

		static Memory& instance() {
			static Memory m;
			return m;
		}

		void* alloc(int type, int size) {
			auto ptr= std::malloc(size);
			record[ptr] = MemeryItem{ type ,1,0};
			return ptr;
		}

		void free(void* ptr) {
			record.erase(ptr);
		}

		//release 后  指针为空就返回true
		bool release(void* ptr) {
			auto itr=record.find(ptr);
			if (itr == record.end()) {
				return true;
			}
			itr->second.shared_count--;
			bool zero_referance = itr->second.shared_count == 0;
			if (zero_referance) {
				free(ptr);
			}
			return zero_referance;
		}

		bool retain(void* ptr) {
			auto itr = record.find(ptr);
			if (itr == record.end()) {
				return false;
			}
			itr->second.shared_count++;
			return true;
		}

		bool check(void* ptr) {
			auto itr = record.find(ptr);
			return itr != record.end();
		}
	private:
		Memory()
		{
			record.clear();
		}
	};

}