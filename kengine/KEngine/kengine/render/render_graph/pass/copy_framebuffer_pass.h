#pragma once
#include "pass.h"
namespace kengine {
	enum class FrameBufferComponent {
		COLOR = GL_COLOR_BUFFER_BIT,
		DEPTH = GL_DEPTH_BUFFER_BIT,
		STENCIL = GL_STENCIL_BUFFER_BIT,
		COLOR_DEPTH = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
		COLOR_STENCIL = GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
		DEPTH_STENCIL = GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
		COLOR_DEPTH_STENCIL = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT,
	};
	class CopyFrameBufferPass :public Pass
	{
	public:
		RenderTargetPtr src;
		RenderTargetPtr dist;
		Regioni src_region;
		Regioni dist_region;
		FrameBufferComponent component= FrameBufferComponent::COLOR;
		uint32 filter = GL_LINEAR;
		CopyFrameBufferPass() = delete;
		CopyFrameBufferPass(RenderTargetPtr src,RenderTargetPtr dist,Regioni& src_region, Regioni& dist_region, FrameBufferComponent component = FrameBufferComponent::COLOR, uint32 filter = GL_LINEAR) :
			src(src),
			dist(dist),
			src_region(src_region),
			dist_region(dist_region),
			component(component),
			filter(filter){}
		void exec(Scene& scene, RenderDataPtr render_data, Pipeline& pipeline) override {
			glBindFramebuffer(GL_READ_FRAMEBUFFER, src->gpu_id);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dist->gpu_id);
			glBlitFramebuffer(src_region.x0, src_region.y0, src_region.x1, src_region.y1, dist_region.x0, dist_region.y0, dist_region.x1, dist_region.y1,(GLbitfield)component, filter);
		}
	};
}