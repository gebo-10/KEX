#pragma once
#include <kengine/environment.h>
#include <kengine/scene/component.h>
#include <kengine/scene/component/transform.h>
#include <kengine/core/math/kmath.h>
namespace kengine {
	class ArcballMonitor: public Component
	{
	public:
		TransformPtr tr;
		ArcballMonitor():Component(ComponentType::ARCBALL_MONITOR)
		{
			
		}

		~ArcballMonitor()
		{
		}

		void aweak() override;

		void update()override {
			static float r = 0;
			r += 0.1;
			mat4 identity(1.f);
			mat4 m = glm::mat4_cast(Quaternion(glm::radians(vec3(0, r, 0))))*glm::translate(identity, vec3(0, 1.0, -5.0f)) ;
			tr->set_matrix(m);
		}

	};

}