#pragma once
#include "core/base/type.h"
//#include"core/config/config.h"
//#include"core/debug/debug.h"
//#include"core/debug/memory_monitor.h"
#include"core/base/log.h"
#include "application.h"

#include "environment.h"

namespace kengine
{
	class KEngine {
	public:
		//Environment env;
		//RenderSystem render_system;
		//ResourceManager resource_manager;
		KEngine() {}
		Application* app;
	
		void init();
		void update();
		void quit();
		void on_view_size(int width, int height);

	private:
	
	};
}
kengine::KEngine& GetKEngineInstance();