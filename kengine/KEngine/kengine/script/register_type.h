#pragma once
#include <kengine/core/base/base.h>
#include<sol.hpp>
namespace kengine {
	class RegisteLuaType
	{
	public:
		RegisteLuaType()
		{
		}

		~RegisteLuaType()
		{
		}
		static void reg_all(sol::state& lua) {
			reg_color(lua);
			reg_rect(lua);
		}
		static void reg_color(sol::state & lua) {
			sol::usertype<Color> type = lua.new_usertype<Color>("Color",
				// 3 constructors
				sol::constructors<Color(), 
				Color(float r, float g, float b, float a),
				Color(float r, float g, float b)>()
			);
		
			type["r"] = &Color::r;
			type["g"] = &Color::g;
			type["b"] = &Color::b;
			type["a"] = &Color::a;
		}

		static void reg_rect(sol::state& lua) {
			{
				sol::usertype<Rect> type = lua.new_usertype<Rect>("Rect",
					sol::constructors<Rect(),
					Rect(int x, int y, int w, int h)>()
					);

				type["x"] = &Rect::x;
				type["y"] = &Rect::y;
				type["w"] = &Rect::w;
				type["h"] = &Rect::h;
			}
			{
				sol::usertype<Rectf> type = lua.new_usertype<Rectf>("Rectf",
					sol::constructors<Rectf(),
					Rectf(float x, float y, float w, float h)>()
					);

				type["x"] = &Rectf::x;
				type["y"] = &Rectf::y;
				type["w"] = &Rectf::w;
				type["h"] = &Rectf::h;
			}
		}

	};

}