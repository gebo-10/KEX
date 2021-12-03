#pragma once
#include "monitor_processor.h"
namespace kengine {
	class TestProcessor : public MonitorProcessor
	{
	public:
		TestProcessor()
		{
		}

		virtual ~TestProcessor()
		{
		}
		virtual void process(flexbuffers::Map revc, flexbuffers::Builder& result) {
			auto s = revc["content"].AsString();

			info("recv {}", s.c_str());
			result.StartMap();
			result.Add("content", "adsfjladsjfla");
			result.EndMap(0);
		}
	};
}