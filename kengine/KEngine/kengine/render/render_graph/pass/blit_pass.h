#pragma once
#include "pass.h"
namespace kengine {
	class BlitPass :public Pass
	{
	public:
		RenderTargetPtr render_target;
		MaterialPtr material;
		MeshPtr plane=nullptr;
		BlitPass() = delete;
		BlitPass( RenderTargetPtr render_target, MaterialPtr material) :render_target(render_target),material(material){
			plane = std::make_shared<PlaneMesh>();
		}
		void exec(Scene& scene, Pipeline& pipeline) override {
			//pipeline.set_state(std::make_shared<ClearValue>(color_pink, 1.0f, 0));
			pipeline.set_state(std::make_shared<DepthTest>(false, CompareFunc::LEQUAL));
			pipeline.set_target(render_target);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			pipeline.use_material(material);
			Matrix I(1.0);
			pipeline.draw(I, plane);
		}
	};
}