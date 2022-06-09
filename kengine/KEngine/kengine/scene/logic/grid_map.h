#pragma once
#include <kengine/environment.h>
#include <kengine/scene/component.h>
#include <kengine/scene/component/transform.h>
#include <kengine/core/math/kmath.h>
#include <kengine/scene/component/mesh_render.h>
namespace kengine {
	class GridMap : public Component
	{
	public:
		MeshRenderPtr mesh_render;
		TexturePtr texture;
		BufferPtr data;
		GridMap() :Component(ComponentType::GRID_MAP)
		{

		}

		~GridMap()
		{
		}

		void start() override;

		void update() {
			texture->update_data(data);
		}

	};
}