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

		std::vector<GameObjectPtr> objs;
		TransformComponentPtr comp_transform;
		void init() {
			auto obj = std::make_shared<GameObject>();

			comp_transform = std::make_shared<TransformComponent>();
			comp_transform->transform.position.z = 0;
			obj->add_component(comp_transform);

			auto comp_mesh = std::make_shared<MeshRender>();
			comp_mesh->material= Env.assets_database.get_resource<Material>(NAME("Assets/Bundle/default.material"));
			comp_mesh->mesh = Env.assets_database.get_resource<Mesh>(NAME("Assets/Bundle/box.fbx"));
			obj->add_component(comp_mesh);

			objs.push_back(obj);
		}

		std::vector<GameObjectPtr>& cull() {
			comp_transform->transform.rotate.x += 10;
			return objs;
		}
	private:

	};
	typedef shared_ptr<Scene> ScenePtr;
}