#pragma once
#include "glm_math.h"
namespace kengine {
	template<class T>
	class RegionT
	{
	public:
		T x0;
		T y0;
		T x1;
		T y1;
		RegionT() : x0(0), y0(0), x1(0), y1(0) {}
		RegionT(T x0, T y0, T x1, T y1) : x0(x0), y0(y0), x1(x1), y1(y1) {}
		~RegionT() {}
		bool operator ==(RegionT& c) {
			return this->x0 == c.x && this->y0 == c.y && this->x1 == c.w && this->y1 == c.h;
		}

		bool operator !=(RegionT& c) {
			return this->x0 != c.x || this->y0 != c.y || this->x1 != c.w || this->y1 != c.h;
		}

		//void set(ivec2 pos, ivec2 size) {
		//	x = pos.x;
		//	y = pos.y;
		//	width = size.x;
		//	height = size.y;
		//}
	};
	typedef RegionT<int> Region;
	typedef RegionT<int> Regioni;
	typedef RegionT<float> Regionf;
}