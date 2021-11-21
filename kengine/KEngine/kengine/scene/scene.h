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
		void init() {
			auto shader = Env.assets_database.get_resource<Shader>(NAME("Assets/Bundle/default.glsl"));
			auto mesh = Env.assets_database.get_resource<Mesh>(NAME("Assets/Bundle/box.fbx"));
			

			auto obj = std::make_shared<GameObject>();

			auto comp_transform = std::make_shared<TransformComponent>();
			comp_transform->transform.position.z = 5;
			obj->add_component(comp_transform);

			auto comp_mesh = std::make_shared<MeshRender>();
			comp_mesh->material = std::make_shared<Material>(shader);
			comp_mesh->mesh = mesh;
			obj->add_component(comp_mesh);

			objs.push_back(obj);
		}

		std::vector<GameObjectPtr>& cull() {
			return objs;
		}
	private:

	};
	typedef shared_ptr<Scene> ScenePtr;
}