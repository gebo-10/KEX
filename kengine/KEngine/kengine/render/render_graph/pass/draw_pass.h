#pragma once
#include "pass.h"

namespace kengine {
	class DrawPass :public Pass
	{
	public:
		std::vector<TexturePtr> input;
		RenderTargetPtr target;
		CameraPtr camera;
		std::function<std::vector<GameObject>()> cull;
		std::function<std::vector<GameObject>()> filter;
		std::function<std::vector<GameObject>()> sort;
		// 
		//virtual Matrix get_view_matrix() {}
		//virtual Matrix get_project_matrix() {}
		//virtual GameObject cull(){}
		DrawPass()
		{
			camera = std::make_shared<Camera>();
			camera->set_type(Camera::PERSPECTIVE);
			camera->set_ortho(-400, 400, -400, 400);
			camera->lookat(vec3(0, 5, 5), vec3(0, 0, 0), vec3(0, 1, 0));
		}

		virtual void exec(Scene& scene, Pipeline& pipeline) {
			pipeline.common_uniform.v = camera->get_v();
			pipeline.common_uniform.p = camera->get_p();
			pipeline.sync_common_uniform();

			auto objs = scene.cull();
			for (auto obj : objs) {
				TransformComponentPtr t= std::dynamic_pointer_cast<TransformComponent> ( obj-> get_component(ComponentType::TRANSFORM) );
				MeshRenderPtr m = std::dynamic_pointer_cast<MeshRender> (obj->get_component(ComponentType::MESH_RENDER));
				pipeline.use_material(m->material);
				pipeline.draw(t->transform.matrix(), m->mesh);
			}
		}
	};
}