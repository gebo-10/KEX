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
			auto view_port = scene.get_camera_view_port(camera_id);
			pipeline.set_state(std::make_shared<ViewPortState>(view_port));

			pipeline.set_state(std::make_shared<ScissorState>(true,view_port));
			pipeline.set_state(std::make_shared<ClearValue>(color_pink, 1.0f, 0));
			glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

			pipeline.common_uniform.v = scene.get_camera_v(camera_id);
			pipeline.common_uniform.p = scene.get_camera_p(camera_id);
			pipeline.common_uniform.pv = pipeline.common_uniform.p * pipeline.common_uniform.v;

			pipeline.common_uniform.light_dir =  vec4(-1, -1, 1, 0);
			pipeline.common_uniform.light_color = color_purple;

			pipeline.sync_common_uniform();

			//auto ssbo = std::make_shared<GPUBuffer>(100 * sizeof(float), GPUBufferType::SHADER_STORAGE_BUFFER, GPUBufferHit::DYNAMIC_DRAW);
			//ssbo->bind_to_point(GPUBufferType::SHADER_STORAGE_BUFFER, 10);

			auto objs = scene.cull();
			//float* res2=nullptr;
			for (auto obj : objs) {
				TransformPtr t= std::dynamic_pointer_cast<Transform> ( obj-> get_component(ComponentType::TRANSFORM) );
				MeshRenderPtr m = std::dynamic_pointer_cast<MeshRender> (obj->get_component(ComponentType::MESH_RENDER));
				//res2 = (float*)m->mesh->mesh_buffer[MeshBufferType::POSITION].buffer->data;
				pipeline.use_material(m->material);
				pipeline.draw(t->matrix(), m->mesh,m->instance_count);
			}

			//glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
			//glFinish();
			//
			//float* res = (float*)ssbo->map(GPUBufferHit::READ_ONLY);
			//
			//for (int i = 0; i <24; i++)
			//{
			//	std::cout << res[i*4+0] << " " << res[i * 4 + 1] << " " << res[i * 4 + 2] << " " << res[i * 4 + 3] << std::endl;
			//	std::cout << res2[i * 3 + 0] << " " << res2[i * 3 + 1] << " " << res2[i * 3 + 2] << std::endl;
			//}
			return;
		}
	};
}