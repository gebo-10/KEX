#pragma once
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
		virtual void process(BufferPtr recv, BufferPtr result) = 0;
	};
}