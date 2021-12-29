#pragma once
#include"../component.h"
#include <kengine/core/math/kmath.h>
namespace kengine {
	enum class LightType{
		Point,
		Directional,
		Spot,
	};
	class Light:public Component
	{
	public:
		LightType type;
		bool accept_cull=false;  //是否视锥体裁剪
		//vec3 position;  // 灯的位置  transform 提供
		//vec3 direction; // 方向光源
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;

		float constant; // 衰减常数  //vec4
		float linear;   // 衰减一次系数
		float quadratic; // 衰减二次系数
		float cutoff;   // 聚光灯张角的余弦值
		Light():Component(ComponentType::LIGHT)
		{
		}

		~Light()
		{
		}

	private:

	};

}