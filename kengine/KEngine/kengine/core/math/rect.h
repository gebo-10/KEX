#pragma once
#include "glm_math.h"
namespace kengine{
	template<class T>
	class RectT
	{
	public:
		T x;
		T y;
		T w;
		T h;
		RectT() : x(0), y(0), w(0), h(0) {}
		RectT(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
		~RectT() {}
		bool operator ==(RectT& c) {
			return this->x == c.x && this->y == c.y && this->w == c.w && this->h == c.h;
		}

		bool operator !=(RectT& c) {
			return this->x != c.x || this->y != c.y || this->w != c.w || this->h != c.h;
		}

		//void set(ivec2 pos, ivec2 size) {
		//	x = pos.x;
		//	y = pos.y;
		//	width = size.x;
		//	height = size.y;
		//}
	};
	typedef RectT<int> Rect;
	typedef RectT<float> Rectf;
}