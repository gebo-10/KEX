//#pragma once
//class Memory {
//    Memory();
//#ifdef DEBUG_ENABLED
//    static SafeNumeric<uint64_t> mem_usage;
//	static SafeNumeric<uint64_t> max_usage;
//#endif
//
//    static SafeNumeric<uint64_t> alloc_count;
//
//public:
//    static void *alloc_static(size_t p_bytes, bool p_pad_align = false);
//    static void *realloc_static(void *p_memory, size_t p_bytes, bool p_pad_align = false);
//    static void free_static(void *p_ptr, bool p_pad_align = false);
//
//    static uint64_t get_mem_available();
//    static uint64_t get_mem_usage();
//    static uint64_t get_mem_max_usage();
//};
//
////class DefaultAllocator {
////public:
////    _FORCE_INLINE_ static void *alloc(size_t p_memory) { return Memory::alloc_static(p_memory, false); }
////    _FORCE_INLINE_ static void free(void *p_ptr) { Memory::free_static(p_ptr, false); }
////};

#pragma once
#include"type.h"
namespace kengine {
	enum class Endian
	{
		Little,
		Big,
	};
	class Memery
	{
	public:
		Memery()
		{
		}

		~Memery()
		{
		}

		static Endian endian() {
			union{
				short i;
				char a[2];
			}u;
			u.a[0] = 0x11;
			u.a[1] = 0x22;
			if (u.i == 0x2211) {
				return Endian::Little;
			}
			else {
				return Endian::Big;
			}
		}
		//uint32_t htonl(uint32_t hostlong);
		//uint16_t htons(uint16_t hostshort);
		//uint32_t ntohl(uint32_t netlong);
		//uint16_t ntohs(uint16_t netshort);
		static uint16 ntohs(uint16 netshort) {
			if (endian() == Endian::Big) {
				return netshort;
			}
			else {
				union {
					uint16 i;
					uint8 a[2];
				}u;
				u.i = netshort;
				uint8 tmp = u.a[0];
				u.a[0] = u.a[1];
				u.a[1] = tmp;
				return u.i;
			}
		}

		static int32 ntohi(int32 netshort) {
			if (endian() == Endian::Big) {
				return netshort;
			}
			else {
				union {
					int32 i;
					uint8 a[4];
				}u1,u2;
				u1.i = netshort;
				u2.i = netshort;
				u1.a[0] = u2.a[3];
				u1.a[1] = u2.a[2];
				u1.a[2] = u2.a[1];
				u1.a[3] = u2.a[0];
				return u1.i;
			}
		}
	private:

	};

}