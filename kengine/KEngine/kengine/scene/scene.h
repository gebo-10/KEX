#pragma once
#include <kengine/core/base/base.h>
#include "component/camera.h"
#include "game_object.h"
#include <kengine/util/mesh_importer.h>
namespace kengine {
	class RenderGraph;
	typedef shared_ptr< RenderGraph> RenderGraphPtr;
	class Scene
	{
	public:
		GameObjectPtr root;
		RenderGraphPtr render_graph;
		std::vector< GameObjectPtr > cameras; //light 下挂载一个camera 阴影

		Scene()
		{
		}

		~Scene()
		{
		}

		std::vector<GameObjectPtr> objs;
		TransformPtr comp_transform;
		int rotate=0;
		void init() {
			root = std::make_shared<GameObject>();

			comp_transform = std::make_shared<Transform>();
			root->add_component(comp_transform);

			auto comp_mesh = std::make_shared<MeshRender>();
			comp_mesh->material= Env.assets_database.get_resource<Material>(NAME("Assets/Bundle/per_frag_diffuse.material"));
			comp_mesh->mesh = Env.assets_database.get_resource<Mesh>(NAME("Assets/Bundle/box.fbx"));
			//comp_mesh->mesh = MeshImporter::import("main/mesh/bird.FBX");
			comp_mesh->mesh->gpucache();
			root->add_component(comp_mesh);

			objs.push_back(root);

			{
				GameObjectPtr camera_go = std::make_shared<GameObject>();
				CameraPtr camera;
				camera = std::make_shared<Camera>();
				camera->set_type(CameraType::PERSPECTIVE);
				camera->set_view_rect(0.5, 0.5, 0.5, 0.5);
				camera_go->add_component(camera);

				auto camera_transform = std::make_shared<Transform>();
				camera_transform->set_translate(vec3(0, 2, -10));
				camera_go->add_component(camera_transform);
				//camera->lookat(vec3(0, 5, 5), vec3(0, 0, 0), vec3(0, 1, 0));
				cameras.push_back(camera_go);
			}
			/// ///////////////////////////////////////////////////////////////
			{
				GameObjectPtr camera_go = std::make_shared<GameObject>();
				CameraPtr camera = std::make_shared<Camera>();
				camera->set_type(CameraType::PERSPECTIVE);
				camera->set_view_rect(0, 0, 0.5, 0.5);
				camera->set_clear_color(color_blue);
				camera_go->add_component(camera);

				auto camera_transform = std::make_shared<Transform>();
				camera_transform->set_translate(vec3(0, -2, -8));
				camera_go->add_component(camera_transform);
				cameras.push_back(camera_go);
			}
			/// ///////////////////////////////////////////////////////////////
		}

		std::vector<GameObjectPtr>& cull() {
			rotate += 1;
			comp_transform->set_rotate(vec3(0, rotate, 0));
			return objs;
		}

		Matrix get_camera_v(int index) {
			auto comp= cameras[index]->get_component(ComponentType::TRANSFORM);
			auto tp = std::dynamic_pointer_cast<Transform>(comp);
			return glm::inverse(tp->matrix());
			
		}
		Matrix get_camera_p(int index) {
			auto comp = cameras[index]->get_component(ComponentType::CAMERA);
			auto camera = std::dynamic_pointer_cast<Camera>(comp);
			return camera->get_p();
		}

		Rect get_camera_view_port(int index) {
			auto comp = cameras[index]->get_component(ComponentType::CAMERA);
			auto camera = std::dynamic_pointer_cast<Camera>(comp);
			return camera->get_view_port();
		}
	private:

	};
	typedef shared_ptr<Scene> ScenePtr;
}