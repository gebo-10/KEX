#pragma once
#include "../gpu_type.h"
#include <kengine/core/base/base.h>
namespace kengine {
	enum class PipelineStateType {
		//Rasterization
		CULL_FACE,
		POLYGON_OFFSET_FILL,
		LINE_WIDTH,

		//Per-Fragment Operations
		SCISSOR_TEST,
		SAMPLE_COVERAGE,
		BLEND_MODE,
		DEPRH_TEST,
		STENCIL_TEST,
		DITHER,

		//Framebuffer
		CLEAR_STATE,
		MASK_STATE,

		//Camera
		DEPTH_RANGE,
		VIEW_PORT,

		PIPELINE_STATE_TYPE_NUM,
	};
	


	

	enum class DepthTest{
		NONE,
		NEVER,
		ALWAYS,
		LESS,
		GREATER,
		EQUAL,
		LEQUAL,
		GEQUAL,
		NOTEQUAL
	};

	enum class StencilTest {
		NONE,
		NEVER,
		ALWAYS,
		LESS,
		GREATER,
		EQUAL,
		LEQUAL,
		GEQUAL,
		NOTEQUAL
	};

	class PipelineState {
	public:
		PipelineStateType type;
		virtual ~PipelineState(){}
		//virtual PipelineState& operator=(const PipelineState& rhs) {}
		//virtual bool operator==(const PipelineState& rhs){}
		virtual void set(PipelineStatePtr state) {}
	};
	typedef shared_ptr<PipelineState> PipelineStatePtr;	
}