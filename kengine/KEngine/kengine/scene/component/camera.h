#pragma once
#include"../component.h"
namespace kengine {
	class Camera :public Component
	{
	public:
		//viewport
		//depth range
		Camera():Component(ComponentType::CAMERA)
		{
		}

		~Camera()
		{
		}

	private:

	};
	typedef shared_ptr<Camera> CameraPtr;
}