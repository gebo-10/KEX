#pragma once
#include <kengine/core/base/base.h>
//#include"core/config/config.h"
//#include"core/debug/debug.h"
//#include"core/debug/memory_monitor.h"
#include"core/base/log.h"
#include "application.h"

#include "environment.h"
#include "render/render.h"
#include "system/monitor/monitor.h"
#include <kengine/scene/scene_manager.h>
#include <kengine/ui/ui.h>
#include <kengine/script/lua_engine.h>
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
		UI ui;
		Monitor monitor;
		LuaEngine lua_engine;
		void init(int width, int height);
		void update();
		void quit();
		void on_view_size(int width, int height);

	private:
	
	};
}
kengine::KEngine& GetKEngineInstance();