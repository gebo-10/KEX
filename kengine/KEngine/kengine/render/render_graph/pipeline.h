#pragma once
#include <kengine/resource/ram/mesh.h>
#include <kengine/resource/ram/material.h>
#include "../gpu_type.h"
#include "../pipeline_state/all_state.h"
#include "render_target.h"
#include "common_uniform.h"

namespace kengine {
	class Pipeline
	{
	public:
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
		}

		void draw(Matrix m, MeshPtr mesh, int count) {
			//glDisable(GL_CULL_FACE);
			//glFrontFace(GL_CW);
			//glEnable(GL_DEPTH_TEST);
			//glEnable(GL_TEXTURE_2D);
			//glEnable(GL_TEXTURE_2D_MULTISAMPLE);
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			material->set_model_matrix(m);
			mesh->draw(count);
			//mesh->draw_instance(6);
		}

		void set_target(RenderTargetPtr t) {
			if (t == target) {
				return;
			}
			target = t;
			if (t == nullptr) {
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				return;
			}
			t->bind();
		}

		void use_material(MaterialPtr m) {
			if (m == material) {
				return;
			}
			material = m;
			m->bind();
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
