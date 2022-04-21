#pragma once
#include <kengine/core/base/base.h>
#include "component/camera.h"
#include <kengine/util/mesh_importer.h>
#include <kengine/util/texture_importer.h>
#include <kengine/util/mat_glsl_importer.h>
#include <kengine/util/skin_importer.h>
#include <kengine/resource/buildin/plane_mesh.h>
#include <kengine/scene/object.h>

namespace kengine {
	struct CameraData {
		//int camera_id;
		Color clear_color;
		Rectf viewport;
		vec4 position;
		mat4 v;
		mat4 p;
		mat4 pv;
	};
	struct LightData {
		ivec4 type;		//LightType type;
		vec4 position;  // 灯的位置  transform 提供
		vec4 direction; // 方向光源
		Color ambient;
		Color diffuse;
		Color specular;
		vec4 param; // 衰减常数 // 衰减一次系数// 衰减二次系数 // 聚光灯张角的余弦值
	};
	struct MeshData {
		int id;
		int instance;
		mat4 matrix;
		MeshPtr mesh;
		MaterialPtr material;
	};
	struct CullData {
		int camera_id;
		std::vector<int> light_ids;
		std::vector<int> mesh_ids; //不透明 材质排序  透明 深度排序
	};
	struct RenderData {
		std::vector<CameraData> camera_datas;
		std::vector<LightData> light_datas;
		std::vector<mat4> matrixs;
		std::vector<MeshData> mesh_datas;
		std::map<int, CullData> cull_datas;
	};
	typedef shared_ptr< RenderData> RenderDataPtr;
	class RenderGraph;
	typedef shared_ptr< RenderGraph> RenderGraphPtr;
	class Scene
	{
	public:
		RenderGraphPtr render_graph;
		ObjectPtr root;
		//std::vector< ObjectPtr > objects;
		//std::vector< ObjectPtr > cameras; //light 下挂载一个camera 阴影
		//std::vector< ObjectPtr > lights;
		Scene()
		{
		}

		~Scene()
		{
		}

		TransformPtr comp_transform;
		TransformPtr light_transform;
		int rotate=0;
		void init() {
			root = std::make_shared<Object>();

			auto object1 = std::make_shared<Object>();
			comp_transform = std::make_shared<Transform>();
			object1->add_component(comp_transform);

			auto comp_mesh = std::make_shared<MeshRender>();
			comp_mesh->instance_count = 1;
			//comp_mesh->material= Env.assets_database.get_resource<Material>(NAME("Assets/Bundle/per_frag_diffuse.material"));
			comp_mesh->material = MatGLSLImport::import("main/material/default.mg");
			//comp_mesh->material = MatGLSLImport::import("main/material/vertex_animation.mg");
			//auto texture = TextureImporter::import("main/texture/miku.png");
			auto texture = TextureImporter::import("main/texture/CesiumMan.jpg",true); 
			comp_mesh->material->add_texture(1, texture);

			//comp_mesh->mesh = Env.assets_database.get_resource<Mesh>(NAME("Assets/Bundle/box.fbx"));
			//comp_mesh->mesh = MeshImporter::import("main/mesh/planet.obj");
			comp_mesh->mesh = std::make_shared<PlaneMesh>();

			object1->add_component(comp_mesh);


			//auto skin = SkinImporter::import("main/mesh/CesiumMan.gltf");
			//skin->init(comp_mesh->mesh, MatGLSLImport::import("main/material/bone_transform.cs.mg") );
			//object1->add_component(skin);

			root->add_child(object1);

			/// ///////////////////////////////////////////////////////////////
			{
				ObjectPtr camera_go = std::make_shared<Object>();
				CameraPtr camera = std::make_shared<Camera>();
				camera->set_type(CameraType::PERSPECTIVE);
				camera->set_view_rect(0, 0, 1, 1);
				camera->set_clear_color(color_black);
				camera_go->add_component(camera);

				auto camera_transform = std::make_shared<Transform>();
				camera_transform->set_translate(vec3(0, 1, -5));
				//camera_transform->set_rotate(vec3(0, 180, 0));
				camera_go->add_component(camera_transform);
				//cameras.push_back(camera_go);
				root->add_child(camera_go);
			}
			/// ///////////////////////////////////////////////////////////////
			{
				ObjectPtr camera_go = std::make_shared<Object>();
				CameraPtr camera;
				camera = std::make_shared<Camera>();
				camera->set_type(CameraType::PERSPECTIVE);
				camera->set_view_rect(0.5, 0.5, 0.5, 0.5);
				camera->set_clear_color(color_green);
				camera_go->add_component(camera);

				auto camera_transform = std::make_shared<Transform>();
				camera_transform->set_translate(vec3(0, 0.5, -4));
				camera_go->add_component(camera_transform);
				//cameras.push_back(camera_go);
				root->add_child(camera_go);
			}
			/// ///////////////////////////////////////////////////////////////
			{
				ObjectPtr object = std::make_shared<Object>();
				auto light = std::make_shared<Light>();
				light->type = LightType::Directional;
				light->ambient = color_green *0.2 ;
				light->diffuse = color_pink;
				light->specular = color_red;
				object->add_component(light);

				auto transform = std::make_shared<Transform>();
				//transform->set_translate(vec3(0, 0, 0));
				transform->set_rotate(vec3(0, -90, 45) );
				object->add_component(transform);
				root->add_child(object);
			}
			/// ///////////////////////////////////////////////////////////////
			{
				ObjectPtr light_root = std::make_shared<Object>();
				{
					auto transform = std::make_shared<Transform>();
					//transform->set_translate(vec3(0, 0, 0));
					//transform->set_rotate(vec3(0, -90, 45));
					light_root->add_component(transform);
					light_transform = transform; //test
				}
				root->add_child(light_root);

				ObjectPtr object = std::make_shared<Object>();
				auto light = std::make_shared<Light>();
				light->type = LightType::Point;
				light->ambient = color_green * 0.2;
				light->diffuse = color_pink;
				light->specular = color_red;
				object->add_component(light);

				auto transform = std::make_shared<Transform>();
				transform->set_translate(vec3(2, 0, 0));
				//transform->set_rotate(vec3(0, -90, 45));
				object->add_component(transform);
				
				light_root->add_child(object);
			}
		}
		
		void update() {
			rotate += 1;
			comp_transform->set_scale(vec3(10, 10, 10));
			comp_transform->set_rotate(vec3(90, 0, 0));
			comp_transform->set_translate(vec3(0, 0, 0));

			light_transform->set_rotate(vec3(0, rotate, 0));
			//light_transform->set_translate(vec3(2, 0, 0));
			
		}

		void trave(ObjectPtr object, mat4 father_matrix, bool consider_active,std::function<void(ObjectPtr object, mat4 matrix)> op) {
			if (consider_active && (!object->active)) {
				return;
			}
			auto comp = object->get_component(ComponentType::TRANSFORM);
			mat4 local_matrix(1.0);
			if (comp != nullptr) {
				auto local_transform = std::dynamic_pointer_cast<Transform>(comp);
				local_matrix = local_transform->matrix();
			}
			auto global_matrix = father_matrix * local_matrix;
			op(object, global_matrix);
			for (auto& child : object->children) {
				trave(child, global_matrix, consider_active, op);
			}
		}
		RenderDataPtr cull() {
			auto render_data = std::make_shared<RenderData>();
			trave(root, mat4(1.0), true, [&](ObjectPtr object, mat4 matrix) {
				auto comp = object->get_component(ComponentType::CAMERA);
				if (comp != nullptr) {
					auto camera= std::dynamic_pointer_cast<Camera>(comp);
					CameraData data;
					data.clear_color = camera->clear_color;
					data.viewport = camera->get_view_port();
					data.position = matrix * vec4(0); //齐次坐标
					data.v = glm::inverse(matrix);
					data.p = camera->get_p();
					data.pv = data.p * data.v;
					render_data->camera_datas.push_back(data);
				}

				comp = object->get_component(ComponentType::MESH_RENDER);
				if (comp != nullptr) {
					auto mesh_render = std::dynamic_pointer_cast<MeshRender>(comp);
					MeshData data;
					data.instance = mesh_render->instance_count;
					data.material = mesh_render->material;
					data.mesh = mesh_render->mesh;
					data.matrix = matrix;
					render_data->mesh_datas.push_back(data);
					render_data->matrixs.push_back(matrix);
				}

				comp = object->get_component(ComponentType::LIGHT);
				if (comp != nullptr) {

					//glm::vec3 scale;
					//glm::quat rotation;
					//glm::vec3 translation;
					//glm::vec3 skew;
					//glm::vec4 perspective;
					//glm::decompose(matrix, scale, rotation, translation, skew, perspective);
					//rotation = glm::conjugate(rotation);

					auto light = std::dynamic_pointer_cast<Light>(comp);
					LightData data;
					data.position = matrix * vec4(0, 0, 0, 1);
					data.direction = matrix * vec4(0, 0, 1, 1); //灯初始方向
					data.type.x = (int)light->type;
					data.ambient =light->ambient;
					data.diffuse = light->diffuse;
					data.specular = light->specular;
					render_data->light_datas.push_back(data);
				}
			});
			return render_data;
		}

	};
	typedef shared_ptr<Scene> ScenePtr;
}