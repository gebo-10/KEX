#include "auto_registe.h"
#include <D:/KEX/tool/AutoBinding/Assets/StreamingAssets/component.h>
void reg_component(sol::table& lua) {
	{
		sol::usertype<kengine::Component> type = lua.new_usertype<kengine::Component>("kengine::Component",
			sol::constructors <
			kengine::Component (kengine::ComponentType)
			> ()
		);
        type["type"] = &kengine::Component::type;
        type["go"] = &kengine::Component::go;
        type["on_attach"] = &kengine::Component::on_attach;
        type["on_dettach"] = &kengine::Component::on_dettach;
	}
}
