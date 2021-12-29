#pragma once
#include "support/config.h"
#include "support/screen.h"
#include "profiler/profiler.h"
#include "support/ktime.h"
#include "platform/platform.h"
#include "core/io/kengine_io.h"
#include"resource/asset/asset_database.h"

#include "service/name_service.h"
#include "service/async_service.h"
#include "service/event_service.h"
#define Env Environment::instance()
#define NAME(str) Env.name_service.get_id(str) 
namespace kengine
{
	class Environment
	{
	public:
		static Environment& instance() {
			static Environment e;
			return e;
		}
		void init()
		{
			config.init();
			time.init();
			profiler.init(config.fps_limit);
			platform.init();
		}
		void update() {
			time.update();
			async_service.update();
		}
		Config config;
		Time time;
		Profiler profiler;
		Platform platform;
		IO* io;

		NameService name_service;
		AsyncService async_service;
		EventService event_service;
		AssetsDatabase assets_database;
	};
}
