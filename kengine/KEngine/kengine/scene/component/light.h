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
		bool accept_cull=false;  //�Ƿ���׶��ü�

		Color ambient;
		Color diffuse;
		Color specular;

		float constant; // ˥������  //vec4
		float linear;   // ˥��һ��ϵ��
		float quadratic; // ˥������ϵ��
		float cutoff;   // �۹���Žǵ�����ֵ
		Light():Component(ComponentType::LIGHT)
		{
		}

		~Light()
		{
		}

	private:

	};

}