#include "grid_map.h"
#include <kengine/scene/object.h>

#include <kengine/util/mesh_importer.h>
#include <kengine/util/texture_importer.h>
#include <kengine/util/mat_glsl_importer.h>
#include <kengine/util/skin_importer.h>
namespace kengine {
	void GridMap::start()
	{
		mesh_render = std::make_shared<MeshRender>();
		go->add_component(mesh_render);
		mesh_render->material = MatGLSLImport::import("main/material/grid_map.mg");

		data = std::make_shared<Buffer>(1024 * 1024 * sizeof(float));
		float* p = (float*)data->data;
		for (int i=0;i<1024*1024;i++)
		{
			//p[i] = (std::rand()%100)/100.0f;

			//p[i] = 0.5f;

			p[i] = i / (1024 * 1024.0f);
		}

		TextureDesc desc;
		desc.width = 1024;
		desc.height = 1024;
		desc.data_format = TextureDataFormat::RED;
		desc.data_type = TextureDataType::FLOAT;
		desc.internal_format = TextureInternalFormat::R32F;
		desc.min_filter = TextureFilterMode::POINT;
		desc.mag_filter = TextureFilterMode::POINT;
		desc.pbo_mode = true;
		desc.memery_size = 1024 * 1024 * sizeof(float);
		//desc.alignment
		texture = std::make_shared<Texture>(desc);
		texture->add_data(data);
		//texture = TextureImporter::import("main/texture/CesiumMan.jpg", true);
		mesh_render->material->add_texture(1, texture);

		mesh_render->mesh = std::make_shared<PlaneMesh>();
		
	}
}


