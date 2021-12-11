#pragma once
#define GLM_LEFT_HANDED
#define GLM_FORCE_LEFT_HANDED
//#define GLM_FORCE_SSE2
//#define GLM_FORCE_ALIGNED
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/ext.hpp>
namespace kengine {
	using Vector2 = glm::highp_vec2;
	using vec2 = glm::highp_vec2;

	using Vector = glm::highp_vec3;
	using Vector3 = glm::highp_vec3;
	using vec3 = glm::highp_vec3;

	using vec4 = glm::highp_vec4;

	using mat3 = glm::mat3;

	using Matrix = glm::mat4;
	using Matrix4 = glm::mat4;
	using mat4 = glm::mat4;


	using Quaternion = glm::quat;
	using Quat = glm::quat;
	using quat = glm::quat;
}