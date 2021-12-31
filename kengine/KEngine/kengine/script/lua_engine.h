#pragma once

#include <sol.hpp>
#include <kengine/core/base/base.h>
#include <kengine/environment.h>
#include "register_type.h"
namespace kengine {
	class LuaEngine
	{
	public:
		sol::state lua;
		sol::protected_function on_event;
		sol::protected_function on_update;
		LuaEngine() :lua(sol::c_call<decltype(&panic), &panic>) {}

		~LuaEngine(){}
		void init() {
			lua.open_libraries(
				sol::lib::base,
				sol::lib::table, 
				sol::lib::os,
				sol::lib::coroutine,
				sol::lib::debug,
				sol::lib::io,
				sol::lib::math,
				sol::lib::package,
				sol::lib::string
				//sol::lib::utf8
			);

			RegisteLuaType::reg_all(lua);

			string search_path = ".\\script\\";
			std::string package_path = lua["package"]["path"];
			lua["package"]["path"] = package_path + ";" + search_path + "?.lua";

			lua.unsafe_script_file("./script/main.lua");
			on_update = lua["Update"];
			on_update.error_handler = lua["OnError"];
			on_event = lua["OnEvent"];
			on_event.error_handler = lua["OnError"];

			sol::protected_function init_function = lua["Init"];
			init_function.error_handler = lua["OnError"];
			init_function();

		}
		static void panic(sol::optional<std::string> maybe_msg) {
			if (maybe_msg) {
				const std::string& msg = maybe_msg.value();
				error("lua error message:{}", msg.c_str());
				system("Pause");
			}
		}

		void reload() {
			sol::protected_function lua_reload = lua["Reload"];
			lua_reload.error_handler = lua["OnError"];
			lua_reload();
		}

		void update() {
			on_update();
		}

		void event() {
			on_event();
		}
	};

}