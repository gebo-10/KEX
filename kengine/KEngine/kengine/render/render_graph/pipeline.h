#pragma once
#include <kengine/resource/ram/mesh.h>
#include <kengine/resource/ram/material.h>
#include "../gpu_type.h"
#include "../pipeline_state/all_state.h"
#include "render_target.h"
#include "common_uniform.h"
#include "bind_point_manager.h"
namespace kengine {
	class Pipeline
	{
	public:
		BindPointManager bind_point_manager;
		CommonUniform common_uniform;
		PipelineStatePtr states[(int)PipelineStateType::PIPELINE_STATE_TYPE_NUM];
		RenderTargetPtr target = nullptr;
		MaterialPtr material;

		Pipeline() {
			states[(int)PipelineStateType::DEPRH_TEST] = std::make_shared<DepthTest>(false,CompareFunc::LEQUAL);
			states[(int)PipelineStateType::STENCIL_TEST] = std::make_shared<StencilTest>(false);
			states[(int)PipelineStateType::CLEAR_VALUE] = std::make_shared<ClearValue>(color_black,1.0f,0);
			states[(int)PipelineStateType::VIEW_PORT] = std::make_shared<ViewPortState>(Rectf(0,0,1,1) );
			states[(int)PipelineStateType::SCISSOR_STATE] = std::make_shared<ScissorState>(false,Rectf(0, 0, 1, 1));

			for (auto state : states) {
				if (state != nullptr) {
					state->setup();
				}
			}

			Env.event_service.listen(EventType::OnViewSize, [this](Event* e) {
				states[(int)PipelineStateType::VIEW_PORT]->setup();
				states[(int)PipelineStateType::SCISSOR_STATE]->setup();
			});
		}

		void draw(int camera_id,Matrix &m, MeshPtr mesh, int count=1) {
			//glEnable(GL_CULL_FACE);
			//glFrontFace(GL_CW);
			//glEnable(GL_DEPTH_TEST);
			//glEnable(GL_TEXTURE_2D);
			//glEnable(GL_TEXTURE_2D_MULTISAMPLE);
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glDisable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
			//glDisable(GL_STENCIL_TEST);

			//if (mesh->has_bone()) {
			//	auto bone_matrix = mesh->get_bone_matrix();
			//	material->set_uniform(5, glm::value_ptr(bone_matrix[0]), bone_matrix.size() *sizeof(mat4));
			//}

			material->set_model_matrix(m);
			material->set_uniform(1, &camera_id);
			//material->set_model_matrix(mat4(1.0));
			
			//material->attach_uniform(bind_point_manager);
			material->attach_uniform();
			mesh->gpucache();
			bind_point_manager.bind_vao(mesh->gpu_object);
		
			mesh->draw(count);
		}

		void set_target(RenderTargetPtr t) {
			if (t == target) {
				return;
			}
			target = t;
			//if (t == nullptr) { //screen render target
			//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
			//	GLenum window_draw_buffers[] = { GL_BACK };
			//	glDrawBuffers(1, window_draw_buffers);
			//	return;
			//}
			t->bind();
		}

		void use_material(MaterialPtr m) {
			if (m == material) {
				return;
			}
			material = m;
			//m->bind();
			m->set_dirty();
			//bind_point_manager.bind_shader(material->shader);
		}

		void set_state(PipelineStatePtr state) {
			PipelineStatePtr origon = states[(int)state->type];
			origon->set(state);
		}
		void sync_common_uniform() {
			common_uniform.sync();
		}
	};
	typedef shared_ptr<Pipeline> PipelinePtr;
}
