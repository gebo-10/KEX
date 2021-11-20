#pragma once
#include "gpu_type.h"
#include "pipeline_state/pipeline_state.h"

#include <kengine/resource/ram/mesh.h>
#include <kengine/resource/ram/material.h>

namespace kengine {
	class CommonUniform {
	public:
		float time;
		Matrix v;
		Matrix p;
		//light
	};
	class Graphics
	{
	public:
		CommonUniform uniform;
		PipelineStatePtr states[(int)PipelineStateType::PIPELINE_STATE_TYPE_NUM];
		//RenderTargetPtr target = nullptr;
		MaterialPtr material;
		void init();
		void destory();

		void set_viewport(Rect rect) {}

		void clear();
		void draw(Matrix m, MeshPtr mesh);
		void use_material(MaterialPtr material);
		void set_state(PipelineStateType type, std::any state);
		//void update_common_uniform(CommonUniform uniform) {}
	};
}
