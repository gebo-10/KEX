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
		}

		virtual void exec(Scene& scene, Pipeline& pipeline) {
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