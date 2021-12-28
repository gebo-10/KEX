#pragma once
#include <kengine/core/base/base.h>
#include "component/camera.h"
#include "game_object.h"
#include <kengine/util/mesh_importer.h>
#include <kengine/util/texture_importer.h>
#include <kengine/util/mat_glsl_importer.h>
#include <kengine/util/skin_importer.h>
#include <kengine/resource/buildin/plane_mesh.h>

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
			comp_mesh->instance_count = 1;
			//comp_mesh->material= Env.assets_database.get_resource<Material>(NAME("Assets/Bundle/per_frag_diffuse.material"));
			comp_mesh->material = MatGLSLImport::import("main/material/default.mg");
			//comp_mesh->material = MatGLSLImport::import("main/material/vertex_animation.mg");
			//auto texture = TextureImporter::import("main/texture/miku.png");
			auto texture = TextureImporter::import("main/texture/CesiumMan.jpg",true); 
			comp_mesh->material->add_texture(1, texture);

			//comp_mesh->mesh = Env.assets_database.get_resource<Mesh>(NAME("Assets/Bundle/box.fbx"));
			comp_mesh->mesh = MeshImporter::import("main/mesh/planet.obj");
			//comp_mesh->mesh = std::make_shared<PlaneMesh>();

			root->add_component(comp_mesh);


			//auto skin = SkinImporter::import("main/mesh/CesiumMan.gltf");
			//skin->init(comp_mesh->mesh, MatGLSLImport::import("main/material/bone_transform.cs.mg") );
			//root->add_component(skin);

			objs.push_back(root);


			{
				GameObjectPtr camera_go = std::make_shared<GameObject>();
				CameraPtr camera;
				camera = std::make_shared<Camera>();
				camera->set_type(CameraType::PERSPECTIVE);
				camera->set_view_rect(0.5, 0.5, 0.5, 0.5);
				camera->set_clear_color(color_transparent);
				camera_go->add_component(camera);

				auto camera_transform = std::make_shared<Transform>();
				camera_transform->set_translate(vec3(0, 0.5, -4));
				camera_go->add_component(camera_transform);
				cameras.push_back(camera_go);
			}
			/// ///////////////////////////////////////////////////////////////
			{
				GameObjectPtr camera_go = std::make_shared<GameObject>();
				CameraPtr camera = std::make_shared<Camera>();
				camera->set_type(CameraType::PERSPECTIVE);
				camera->set_view_rect(0, 0, 1, 1);
				camera->set_clear_color(color_white);
				camera_go->add_component(camera);

				auto camera_transform = std::make_shared<Transform>();
				camera_transform->set_translate(vec3(0, -0, -15));
				//camera_transform->set_rotate(vec3(0, 180, 0));
				camera_go->add_component(camera_transform);
				cameras.push_back(camera_go);
			}
			/// ///////////////////////////////////////////////////////////////
		}
		 
		CameraPtr get_camera(int index) {
			auto comp = cameras[index]->get_component(ComponentType::CAMERA);
			return std::dynamic_pointer_cast<Camera>(comp);
		}

		std::vector<GameObjectPtr>& cull() {
			rotate += 1;
			comp_transform->set_rotate(vec3(90, rotate, 0));
			return objs;
		}
	private:

	};
	typedef shared_ptr<Scene> ScenePtr;
}