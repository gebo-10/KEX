#pragma once
namespace kengine::monitor{
	class Command
	{
	public:
		Command()
		{
		}

		virtual ~Command()
		{
		}
		virtual void process() {}
	private:

	};

}