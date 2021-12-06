#pragma once
#include "core/base/type.h"
//#include"core/config/config.h"
//#include"core/debug/debug.h"
//#include"core/debug/memory_monitor.h"
#include"core/base/log.h"
#include "application.h"

#include "environment.h"
#include "render/render.h"
#include "system/monitor/monitor.h"
#include <kengine/scene/scene_manager.h>
namespace kengine
{
	class KEngine {
	public:
		//Environment env;
		//RenderSystem render_system;
		//ResourceManager resource_manager;

		KEngine() {}
		Application* app;
		
		Render render;
		SceneManager scene_manager;
		Monitor monitor;

		void init(int width, int height);
		void update();
		void quit();
		void on_view_size(int width, int height);

	private:
	
	};
}
kengine::KEngine& GetKEngineInstance();