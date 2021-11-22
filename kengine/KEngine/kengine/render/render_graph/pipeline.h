#pragma once
#include "../gpu_type.h"
#include "../pipeline_state/all_state.h"
#include "render_target.h"
#include <kengine/resource/ram/mesh.h>
#include <kengine/resource/ram/material.h>
#include <kengine/resource/gpu/uniform_buffer.h>

namespace kengine {
	//#pragma pack(4)
	struct CommonUniform { //alignas
	public:
		//float time;
		Matrix v;
		Matrix p;
		Matrix pv;

		UniformBufferPtr uniform_buffer=nullptr;
		void sync() {
			if (uniform_buffer == nullptr) {
				uniform_buffer = std::make_shared<UniformBuffer>(sizeof(CommonUniform) - sizeof(UniformBufferPtr));
			}
			memcpy(uniform_buffer->data,this, sizeof(CommonUniform)-sizeof(int));
		}
	};
	//#pragma pack()
	class Pipeline
	{
	public:
		CommonUniform common_uniform;
		PipelineStatePtr states[(int)PipelineStateType::PIPELINE_STATE_TYPE_NUM];
		RenderTargetPtr target = nullptr;
		MaterialPtr material;

		Pipeline() {
			states[(int)PipelineStateType::CLEAR_VALUE] = std::make_shared<ClearValue>(color_black,0,0);
		}

		void draw(Matrix m, MeshPtr mesh) {
			material->set_model_matrix(m);
			mesh->draw();
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
			//if (origon == state) {
			//	return;
			//}
			origon->set(state);
		}
		void sync_common_uniform() {
			common_uniform.sync();
		}
	};
	typedef shared_ptr<Pipeline> PipelinePtr;
}
