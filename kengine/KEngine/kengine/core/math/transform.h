#pragma once
#include "glm_math.h"
namespace kengine {
	class Transform
	{
	public:
		vec3  position{ 0 };
		vec3  rotate{ 0 };
		vec3  scale{ 1 };
		Transform() {}
		~Transform() {}
		mat4 matrix() {
			mat4 identity(1.f);
			mat4 matrix = translate(identity, position) * glm::mat4_cast(Quaternion(radians(rotate))) * glm::scale(identity, scale);
			return matrix;
		}
	};
}