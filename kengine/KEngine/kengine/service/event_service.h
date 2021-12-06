#pragma once
#include <functional>
#include <map>
namespace kengine {
	enum class EventType
	{
		OnViewSize,
	};
	struct Event
	{
		EventType type;
	};
	struct OnViewSize: Event
	{
		EventType type = EventType::OnViewSize;
		int width;
		int height;
	};
	typedef std::function<void(Event*)> EventCallback;
	class EventService
	{
	public:
		std::map< EventType, std::vector<EventCallback> > event_solt;
		EventService()
		{
		}

		~EventService()
		{
		}

		int listen(EventType type,EventCallback cb) {
			auto it = event_solt.find(type);
			if (it == event_solt.end()) {
				std::vector<EventCallback> cbs;
				cbs.push_back(cb);
				event_solt.insert({ type, cbs });
				return 0;
			}
			else {
				it->second.push_back(cb);
				return it->second.size() - 1;
			}
		}
		
		void unlisten(EventType type, int id) {
			auto it = event_solt.find(type);
			if (it != event_solt.end()) {
				it->second.erase(it->second.begin() + id);
			}
		}

		void dispatch(EventType type, Event* e) {
			auto it = event_solt.find(type);
			if (it != event_solt.end()) {
				for (auto& cb : it->second) {
					cb(e);
				}
			}
		}

	};

}