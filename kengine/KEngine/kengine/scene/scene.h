#pragma once
#include <kengine/core/base/base.h>
#include "component/camera.h"
#include "game_object.h"
namespace kengine {
	class Scene
	{
	public:
		Scene()
		{
		}

		~Scene()
		{
		}

	private:

	};
	typedef shared_ptr<Scene> ScenePtr;
}