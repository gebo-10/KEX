#pragma once
namespace kengine {
	class System
	{
	public:
		System()
		{
		}

		~System()
		{
		}
		virtual void init(){}

		virtual void update(){}

		//virtual void stop();

	};
}