#pragma once
#include "glm_math.h"
namespace kengine {
	class SRT
	{
	public:
		vec3  translate{ 0 };
		vec3  rotate{ 0 };
		vec3  scale{ 1 };
		SRT() {}
		~SRT() {}
		mat4 matrix() {
			mat4 identity(1.f);
			mat4 matrix = glm::translate(identity, translate) * glm::mat4_cast(Quaternion(radians(rotate))) * glm::scale(identity, scale);
			return matrix;
		}
	};
}