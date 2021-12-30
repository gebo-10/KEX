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

		Color ambient;
		Color diffuse;
		Color specular;

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