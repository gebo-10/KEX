#pragma once
#include "../gpu_type.h"
#include "../pipeline_state/all_state.h"
#include "target.h"
#include <kengine/resource/ram/mesh.h>
#include <kengine/resource/ram/material.h>

namespace kengine {
	class CommonUniform {
	public:
		float time;
		Matrix v;
		Matrix p;
	};
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
		//void update_common_uniform(CommonUniform uniform) {}
	};
	typedef shared_ptr<Pipeline> PipelinePtr;
}
