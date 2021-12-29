#include "camera.h"
#include "../object.h"
namespace kengine {
	mat4 Camera::get_v()
	{
		auto comp = go->get_component(ComponentType::TRANSFORM);
		auto tp = std::dynamic_pointer_cast<Transform>(comp);
		return glm::inverse(tp->matrix());
	}
}