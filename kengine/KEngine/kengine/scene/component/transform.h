#pragma once
#include"../component.h"
#include <kengine/core/math/kmath.h>
namespace kengine {
	class Transform :public Component
	{
	private:
		vec3  t{ 0 };
		vec3  r{ 0 };
		vec3  s{ 1 };
		Matrix mat_cache;
		bool dirty = true;
	public:
		Transform():Component(ComponentType::TRANSFORM)
		{
		}

		~Transform()
		{
		}

		mat4 matrix() {
			if (dirty) {
				mat4 identity(1.f);
				mat_cache = glm::translate(identity, t) * glm::mat4_cast(Quaternion(radians(r))) * glm::scale(identity, s);
				dirty = false;
			}
			return mat_cache;
		}

		const vec3 & translate() {
			return  t;
		}
		const vec3& rotate() {
			return  r;
		}
		const vec3& scale() {
			return  s;
		}

		void set_translate(const vec3& v) {
			t=v;
			dirty = true;
		}
		void set_rotate(const vec3& v) {
			r = v;
			dirty = true;
		}
		void set_scale(const vec3& v) {
			s = v;
			dirty = true;
		}

	};
	typedef shared_ptr<Transform> TransformPtr;
}
