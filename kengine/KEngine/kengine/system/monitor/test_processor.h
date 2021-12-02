#pragma once
#include "monitor_processor.h"
#include <flatbuffers/flexbuffers.h>
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
		virtual void process(BufferPtr recv, BufferPtr result) {
			auto root = flexbuffers::GetRoot((uint8_t*)recv->data, recv->size);
			auto v = root.AsVector();
			uint16 type = v[0].AsUInt16();
			auto s = v[1].AsString();

			info("recv {}", s.c_str());
			int count=sprintf_s(result->data,1000, "woroldddddd");
			result->size = count;
		}
	};
}