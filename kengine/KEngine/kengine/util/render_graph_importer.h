#pragma once
#include <kengine/render/render_graph/render_graph.h>
namespace kengine {
	class RenderGraphImporter
	{
	public:
		RenderGraphImporter()
		{
		}

		~RenderGraphImporter()
		{
		}

		static RenderGraphPtr import(const string & filename) {
			CheckGLError
			RenderGraphPtr render_graph = std::make_shared<RenderGraph>();
			auto state_pass = std::make_shared<StatePass>();
			state_pass->states.push_back(std::make_shared<ClearValue>(color_pink, 1.0f, 0));
			state_pass->states.push_back(std::make_shared<DepthTest>(true, CompareFunc::LEQUAL));
			render_graph->passes.push_back(state_pass);

			render_graph->passes.push_back(std::make_shared<ClearPass>(true, true, false));

			auto dp2 = std::make_shared<DrawPass>();
			dp2->camera_id = 1;

			TextureDesc desc;
			desc.width = 1024;
			desc.height = 1024;
			desc.internal_format = TextureInternalFormat::RGBA8;
			dp2->target = std::make_shared<RenderTarget>(std::vector<Attachment>{
				{ AttachmentPoint::COLOR_ATTACHMENT0, std::make_shared<Texture>(desc) },
				{ AttachmentPoint::DEPTH, std::make_shared<RenderBuffer>(1024, 1024, RenderBufferFormat::DEPTH_COMPONENT) },
			});
			render_graph->passes.push_back(dp2);

			//Regioni region(0, 0, 1024, 1024);
			//auto copy_to_screen=std::make_shared<CopyFrameBufferPass>(render_target, SCREEN_TARGET, region, region);
			//render_graph->passes.push_back(copy_to_screen);

			//auto material= MatGLSLImport::import("main/material/copy.mg");
			//material->add_texture(0,texture);
			//auto blit_to_screen = std::make_shared<BlitPass>(SCREEN_TARGET, material);
			//render_graph->passes.push_back(blit_to_screen);


			auto blur_x_target = std::make_shared<RenderTarget>(std::vector<Attachment>{
				{AttachmentPoint::COLOR_ATTACHMENT0, std::make_shared<Texture>(desc)},
			});

			auto blur_y_target = std::make_shared<RenderTarget>(std::vector<Attachment>{
				{AttachmentPoint::COLOR_ATTACHMENT0, std::make_shared<Texture>(desc)},
			});
			auto ori_mat = MatGLSLImport::import("main/material/direction_blur.mg");
			{
				auto material = std::make_shared<Material>(*ori_mat);
				material->add_texture(0, dp2->target->get_texture());
				auto dir = vec2(1, 0);
				material->set_uniform(3, glm::value_ptr(dir));
				auto blur_x = std::make_shared<BlitPass>(blur_x_target, material);
				render_graph->passes.push_back(blur_x);
			}
			{
				auto material = std::make_shared<Material>(*ori_mat);
				material->add_texture(0, blur_x_target->get_texture());
				auto dir = vec2(0, 1);
				material->set_uniform(3, glm::value_ptr(dir));
				auto blur_y = std::make_shared<BlitPass>(blur_y_target, material);
				render_graph->passes.push_back(blur_y);
			}
			
			{
				auto material = std::make_shared<Material>(*ori_mat);
				material->add_texture(0, blur_y_target->get_texture());
				auto dir = vec2(1, 0);
				material->set_uniform(3, glm::value_ptr(dir));
				auto blur_x = std::make_shared<BlitPass>(blur_x_target, material);
				render_graph->passes.push_back(blur_x);
			}
			{
				auto material = std::make_shared<Material>(*ori_mat);
				material->add_texture(0, blur_x_target->get_texture());
				auto dir = vec2(0, 1);
				material->set_uniform(3, glm::value_ptr(dir));
				auto blur_y = std::make_shared<BlitPass>(SCREEN_TARGET, material);
				render_graph->passes.push_back(blur_y);
			}
		

			return render_graph;
		}

		static RenderGraphPtr import2(const string& filename) {
			CheckGLError
			RenderGraphPtr render_graph = std::make_shared<RenderGraph>();
			auto state_pass = std::make_shared<StatePass>();
			state_pass->states.push_back(std::make_shared<ScissorState>(true, Rectf(0, 0, 1, 1)));
			state_pass->states.push_back(std::make_shared<ClearValue>(color_transparent, 1.0f, 0));
			state_pass->states.push_back(std::make_shared<DepthTest>(true, CompareFunc::LESS));
			render_graph->passes.push_back(state_pass);

			render_graph->passes.push_back(std::make_shared<ClearPass>(true, true, true));

			auto dp1 = std::make_shared<DrawPass>();
			dp1->target = nullptr;
			render_graph->passes.push_back(dp1);

			render_graph->passes.push_back(std::make_shared<FencePass>());
			auto dp2 = std::make_shared<DrawPass>();
			dp2->camera_id = 1;
			render_graph->passes.push_back(dp2);
			return render_graph;
		}
	};
}