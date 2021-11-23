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
			auto shader = Env.assets_database.get_resource<Shader>(NAME("Assets/Bundle/default.glsl"));
			auto mesh = Env.assets_database.get_resource<Mesh>(NAME("Assets/Bundle/box.fbx"));

			//auto camera = std::make_shared<Camera>();
			//camera->set_type(Camera::PERSPECTIVE);
			//camera->set_ortho(-400, 400, -400, 400);
			//camera->lookat(vec3(0,5, 5), vec3(0, 0, 0), vec3(0, 1, 0));

			auto obj = std::make_shared<GameObject>();

			comp_transform = std::make_shared<TransformComponent>();
			comp_transform->transform.position.z = 0;
			obj->add_component(comp_transform);

			auto comp_mesh = std::make_shared<MeshRender>();
			comp_mesh->material = std::make_shared<Material>(shader);
			comp_mesh->material->add_uniform(1, ShaderDataType::Color, color_hotpink);
			//comp_mesh->material->add_uniform(1, ShaderDataType::MAT4, camera->get_v());
			//comp_mesh->material->add_uniform(2, ShaderDataType::MAT4, camera->get_p());
			comp_mesh->mesh = mesh;
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