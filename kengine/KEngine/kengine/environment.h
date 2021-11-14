#pragma once
#include "support/config.h"
#include "profiler/profiler.h"
#include "support/ktime.h"
#include "platform/platform.h"
#include "core/io/kengine_io.h"
#include"resource/asset/asset_database.h"

#include "service/name_service.h"
#define Env Environment::instance()
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
		
		Config config;
		Time time;
		Profiler profiler;
		Platform platform;
		IO* io;

		NameService name_service;
		AssetsDatabase assets_database;
	};
}
