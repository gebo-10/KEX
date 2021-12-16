#pragma once
#include"../component.h"
#include <kengine/core/math/kmath.h>
namespace kengine {
	class Transform :public Component
	{
	private:
		bool local_dirty = true;
		//bool global_dirty = true;
		vec3  t{ 0 };
		vec3  r{ 0 };
		vec3  s{ 1 };
		
		Matrix mat_local;
		//Matrix mat_global;
	public:
		Transform():Component(ComponentType::TRANSFORM)
		{
		}

		~Transform()
		{
		}

		void update_local_matrix() {
			if (local_dirty) {
				mat4 identity(1.f);
				mat_local = glm::translate(identity, t) * glm::mat4_cast(Quaternion(radians(r))) * glm::scale(identity, s);
				local_dirty = false;
			}
			
			return;
		}

		mat4 &matrix() {
			update_local_matrix();
			return mat_local;
		}

		inline const vec3 & translate() {
			return  t;
		}
		inline const vec3& rotate() {
			return  r;
		}
		inline const vec3& scale() {
			return  s;
		}

		inline void set_translate(const vec3& v) {
			if (v == t)return;
			t=v;
			local_dirty = true;
		}
		inline void set_rotate(const vec3& v) {
			if (v == r)return;
			r = v;
			local_dirty = true;
		}
		inline void set_scale(const vec3& v) {
			if (v == s)return;
			s = v;
			local_dirty = true;
		}

	};
	typedef shared_ptr<Transform> TransformPtr;
}
