#pragma once
#include "glm_math.h"
namespace kengine {
	class SRT
	{
	public:
		vec3  translate{ 0 };
		vec3  scale{ 1 };
		Quaternion  rotate= Quaternion(glm::radians(vec3(0,0,0)));
		
		mat4 matrix() {
			mat4 identity(1.f);
			mat4 matrix = glm::translate(identity, translate) * glm::mat4_cast(rotate) * glm::scale(identity, scale);
			return matrix;
		}

		void set_rotate(float x, float y, float z) {
			rotate = Quaternion(glm::radians(vec3(x, y, z)));
		}
		void set_rotate(vec3 vec) {
			rotate = Quaternion(glm::radians(vec));
		}
		void set_rotate(float w,float x, float y, float z) {
			rotate = Quaternion(w,x,y,z);
		}

		void set_translate(float x, float y, float z) {
			translate = vec3(x, y, z);
		}

		void set_translate(vec3 vec) {
			translate = vec;
		}

		void set_scale(float x, float y, float z) {
			scale = vec3(x, y, z);
		}

		void set_scale(vec3 vec) {
			scale = vec;
		}
	};
}