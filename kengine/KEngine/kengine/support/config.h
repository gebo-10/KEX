#pragma once

#include<string>
#include<any>
#include<map>

#include <sol.hpp>
namespace kengine {
	class Config
	{
	public:
		int fps_limit;



		sol::state lua; //析构后会释放luatable
		sol::table data;

		//static Config& instacne() {
		//	static Config config;
		//	return config;
		//}

		Config()
		{
			fps_limit = 60;
		}
		~Config() {}
		void init() {
			//lua.open_libraries(sol::lib::base);
			lua.script_file("config.lua");
			data = lua["Config"];
		}
		//int get_window_height();
		//int get_frame_limit();
	private:

	};

}
