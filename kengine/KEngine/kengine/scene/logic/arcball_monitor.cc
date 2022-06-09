#include "arcball_monitor.h"
#include <kengine/scene/object.h>
namespace kengine {
	void ArcballMonitor::aweak()
	{
		tr = std::dynamic_pointer_cast<Transform>(go->get_component(ComponentType::TRANSFORM) );
		//Env.event_service.listen(EventType::OnUpdate, [this](Event* e) {
		//	update();
		//});
	}

}
