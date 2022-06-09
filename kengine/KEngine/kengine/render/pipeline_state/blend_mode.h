#pragma once
#include "pipeline_state.h"
#include <kengine/core/base/color.h>
namespace kengine {
	// Color= Csource*Fsource Equation Cdst*Fdst
	enum class BlendEquation {
		ADD=GL_FUNC_ADD,
		SUBTRACT=GL_FUNC_SUBTRACT,
		REVERSE_SUBTRACT= GL_FUNC_REVERSE_SUBTRACT,
		//MIN,
		//MAX,
	};
	enum class BlendFunc {
		ZERO=GL_ZERO,
		ONE=GL_ONE,
		SRC_ALPHA_SATURATE=GL_SRC_ALPHA_SATURATE,

		SRC_COLOR=GL_SRC_COLOR,
		DST_COLOR = GL_DST_COLOR,
		CONSTANT_COLOR = GL_CONSTANT_COLOR,

		SRC_ALPHA = GL_SRC_ALPHA,
		DST_ALPHA = GL_DST_ALPHA,
		CONSTANT_ALPHA = GL_CONSTANT_ALPHA,

		ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
		ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
		ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
		ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
		ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
		ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
	};

	//enum class EasyBlendFun {
	//	OPACITY,
	//	MIX,
	//	PREBUILD,
	//	ADD,
	//};
	class BlendMode :public PipelineState
	{
	public:
		bool enable = false;
		Color	blend_color=color_white;
		BlendEquation equation= BlendEquation::ADD;
		BlendFunc func_src=BlendFunc::SRC_ALPHA;
		BlendFunc func_dst = BlendFunc::ONE_MINUS_SRC_ALPHA;
		//BlendEquation	rgb_equation;
		//BlendEquation	alpha_equation;

		//BlendFunc srcRGB;
		//BlendFunc dstRGB;
		//BlendFunc srcAlpha;
		//BlendFunc dstAlpha;

		BlendMode(bool enable):PipelineState(PipelineStateType::BLEND_MODE), enable(enable) {}
		~BlendMode(){}
		void set(PipelineStatePtr state) override  {
			auto new_state = std::dynamic_pointer_cast<BlendMode>(state);
			if (enable != new_state->enable) {
				enable = new_state->enable;
				if (enable) {
					glEnable(GL_BLEND);
				}
				else {
					glDisable(GL_BLEND);
				}
			}

			if (blend_color != new_state->blend_color) {
				blend_color = new_state->blend_color;
				glBlendColor(blend_color.r, blend_color.g, blend_color.b, blend_color.a);
			}

			if (equation != new_state->equation) {
				equation = new_state->equation;
				glBlendEquation((GLenum)equation);
			}

			if (func_src != new_state->func_src || func_dst != new_state->func_dst) {
				func_src = new_state->func_src;
				func_dst = new_state->func_dst;
				glBlendFunc((GLenum)func_src, (GLenum)func_dst);
			}

		}
		void setup() override {
			if (enable) {
				glEnable(GL_BLEND);
			}
			else {
				glDisable(GL_BLEND);
			}
			glBlendColor(blend_color.r, blend_color.g, blend_color.b, blend_color.a);
			glBlendEquation((GLenum)equation);
			glBlendFunc((GLenum)func_src, (GLenum)func_dst);
		}
		//void set_sasy_mode(EasyBlendFun mode) {
		//	switch (mode)
		//	{
		//	case EasyBlendFun::OPACITY:
		//		//glDisable(GL_BLEND);
		//		break;
		//	case EasyBlendFun::MIX:
		//		//glEnable(GL_BLEND);
		//		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//		break;
		//	case EasyBlendFun::PREBUILD:
		//		//glEnable(GL_BLEND);
		//		//glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
		//		break;
		//	case EasyBlendFun::ADD:
		//		//glEnable(GL_BLEND);
		//		//glBlendFunc(GL_ONE, GL_ONE);
		//	default:
		//		break;
		//	}
		//}
	};
}