#pragma once
#include <flatbuffers/flexbuffers.h>
namespace kengine {
	enum class MonitorCommandType
	{
		Test,
		Num,
	};
	class MonitorProcessor
	{
	public:
		MonitorProcessor()
		{
		}

		virtual ~MonitorProcessor()
		{
		}
		virtual void process(flexbuffers::Map revc, flexbuffers::Builder& result) = 0;
	};
}