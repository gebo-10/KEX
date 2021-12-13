#pragma once
#include "../gpu_type.h"
#include <kengine/core/base/base.h>
#include <kengine/core/math/kmath.h>
namespace kengine {
	enum class PipelineStateType {
		//Rasterization
		CULL_FACE,
		POLYGON_OFFSET_FILL,
		LINE_WIDTH,

		//Per-Fragment Operations
		SCISSOR_STATE,
		SAMPLE_COVERAGE,
		BLEND_MODE,
		DEPRH_TEST,
		STENCIL_TEST,
		DITHER,

		//Framebuffer
		CLEAR_VALUE,
		FRAMEBUFFER_MASK,

		//Camera
		DEPTH_RANGE,
		VIEW_PORT,

		PIPELINE_STATE_TYPE_NUM,
	};
	
	enum class Face {
		NONE,
		FRONT=GL_FRONT,
		BACK = GL_BACK,
		FRONT_AND_BACK = GL_FRONT_AND_BACK,
	};

	enum class CompareFunc {
		NONE,
		NEVER = GL_NEVER,
		ALWAYS = GL_ALWAYS,
		LESS = GL_LESS,
		GREATER = GL_GREATER,
		EQUAL = GL_EQUAL,
		LEQUAL = GL_LEQUAL,
		GEQUAL = GL_GEQUAL,
		NOTEQUAL = GL_NOTEQUAL
	};

	class PipelineState {
	public:
		PipelineStateType type;
		PipelineState() = delete;
		PipelineState(PipelineStateType t):type(t){}
		virtual ~PipelineState(){}
		//virtual PipelineState& operator=(const PipelineState& rhs) {}
		//virtual bool operator==(const PipelineState& rhs){}
		virtual void set(shared_ptr<PipelineState> state) = 0;
		virtual void setup() = 0;
	};
	typedef shared_ptr<PipelineState> PipelineStatePtr;	
}