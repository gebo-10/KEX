#pragma once
#include "kengine/core/base/base.h"
#include <chrono>
namespace kengine
{
	class Time
	{
	public:
		float elapsed;
		double now;
		int frame_count;

		int fps;

		void init()
		{
			max_fps = 60;
			interval = 1000.0f / max_fps;
			start = std::chrono::system_clock::now();
			last = start;
		}
		void update()
		{
			frame_count++;
			auto n = std::chrono::system_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(n - last);
			float elapsed =duration.count()* std::chrono::microseconds::period::num / (double)std::chrono::microseconds::period::den;

			last = n;
			fps = 1.0f / elapsed;
			if (elapsed < interval)
			{
				float sleep = (interval - elapsed) / 2.0f;
				std::this_thread::sleep_for(std::chrono::milliseconds( static_cast<long long>(sleep) ) );
			}
		}

		void limit()
		{
			auto n = std::chrono::system_clock::now();
			float sleep = (interval - elapsed) / 2.0f;
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(sleep)));
		}



	private:
		std::chrono::system_clock::time_point last;
		std::chrono::system_clock::time_point start;
		float max_fps;
		float interval;
	};
}
