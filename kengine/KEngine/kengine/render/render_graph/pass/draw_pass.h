#pragma once
#include "pass.h"

namespace kengine {
	class DrawPass :public Pass
	{
	public:
		std::vector<TexturePtr> input;
		RenderTargetPtr target;

		int camera_id=0;
		std::function<std::vector<GameObjectPtr>()> cull;
		std::function<std::vector<GameObjectPtr>()> filter;
		std::function<std::vector<GameObjectPtr>()> sort;

		virtual void exec(Scene& scene, Pipeline& pipeline) {
			pipeline.common_uniform.v = scene.get_camera_v(camera_id);
			pipeline.common_uniform.p = scene.get_camera_p(camera_id);
			pipeline.common_uniform.pv = pipeline.common_uniform.p * pipeline.common_uniform.v;
			pipeline.sync_common_uniform();

			auto objs = scene.cull();
			for (auto obj : objs) {
				TransformPtr t= std::dynamic_pointer_cast<Transform> ( obj-> get_component(ComponentType::TRANSFORM) );
				MeshRenderPtr m = std::dynamic_pointer_cast<MeshRender> (obj->get_component(ComponentType::MESH_RENDER));
				pipeline.use_material(m->material);
				pipeline.draw(t->matrix(), m->mesh);
			}
		}
	};
}