#pragma once
#include "pipeline_state.h"
#include <kengine/core/base/color.h>
namespace kengine {
	enum class BlendEquation {
		MIN,
		MAX,
		FUNC_ADD,
		FUNC_SUBTRACT ,
		FUNC_REVERSE_SUBTRACT
	};
	enum class BlendFunc {
		ZERO,
		ONE,
		SRC_ALPHA_SATURATE,

		SRC_COLOR,
		DST_COLOR,
		CONSTANT_COLOR,

		SRC_ALPHA,
		DST_ALPHA,
		CONSTANT_ALPHA,

		ONE_MINUS_SRC_COLOR,
		ONE_MINUS_SRC_ALPHA,
		ONE_MINUS_DST_COLOR,
		ONE_MINUS_CONSTANT_COLOR,
		ONE_MINUS_DST_ALPHA,
		ONE_MINUS_CONSTANT_ALPHA
	};

	enum class EasyBlendFun {
		OPACITY,
		MIX,
		PREBUILD,
		ADD,
	};
	class BlendMode :public PipelineState
	{
	public:
		bool enable = false;
		Color	blend_color;

		BlendEquation	rgb_equation;
		BlendEquation	alpha_equation;

		BlendFunc srcRGB;
		BlendFunc dstRGB;
		BlendFunc srcAlpha;
		BlendFunc dstAlpha;

		BlendMode():PipelineState(PipelineStateType::BLEND_MODE){}
		~BlendMode(){}
		virtual void set(PipelineStatePtr state) {}

		void set_sasy_mode(EasyBlendFun mode) {
			switch (mode)
			{
			case EasyBlendFun::OPACITY:
				//glDisable(GL_BLEND);
				break;
			case EasyBlendFun::MIX:
				//glEnable(GL_BLEND);
				//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				break;
			case EasyBlendFun::PREBUILD:
				//glEnable(GL_BLEND);
				//glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
				break;
			case EasyBlendFun::ADD:
				//glEnable(GL_BLEND);
				//glBlendFunc(GL_ONE, GL_ONE);
			default:
				break;
			}
		}
	};
}