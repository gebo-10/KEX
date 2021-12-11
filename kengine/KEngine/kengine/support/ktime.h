#pragma once
#include "kengine/core/base/base.h"
#include <chrono>
namespace kengine
{
	struct FpsSample {
		float fps_record[4];
		int current=0;
		void sample(float one) {
			fps_record[current] = one;
			current = (current + 1) % 4;
		}
		int fps() {
			float total = 0;
			for (auto f : fps_record) {
				total += f;
			}
			return total / 4.0f;
		}
	};
	class Time
	{
	public:
		float elapsed;
		float now;
		int frame_count;

		FpsSample fps_sample;

		void init()
		{
			max_fps = 50;
			interval = 1000.0f / max_fps;
			start = std::chrono::system_clock::now();
			last = start;
		}
		void update()
		{
			frame_count++;
			auto n = std::chrono::system_clock::now();

			auto tmp=std::chrono::duration_cast<std::chrono::milliseconds>(n - start);
			now = tmp.count() * std::chrono::milliseconds::period::num / (double)std::chrono::milliseconds::period::den;

			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(n - last);
			elapsed =duration.count()* std::chrono::milliseconds::period::num / (double)std::chrono::milliseconds::period::den;

			last = n;
			//fps = 1.0f / elapsed;
			fps_sample.sample(1.0f / elapsed);
			
			if (elapsed < interval)
			{
				//int f = fps();
				//if (f > max_fps) {
				//	sleep_time+=0.1f;
				//}
				//else if (f < max_fps) {
				//	sleep_time-=0.1f;
				//}
				float sleep_time = (interval - elapsed)/2.0f ;
				std::this_thread::sleep_for(std::chrono::milliseconds( static_cast<long long>(sleep_time) ) );
			}
			
		}

		void limit()
		{
			auto n = std::chrono::system_clock::now();
			float sleep = (interval - elapsed) / 2.0f;
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(sleep)));
		}

		int fps() {
			return fps_sample.fps();
		}

	private:
		std::chrono::system_clock::time_point last;
		std::chrono::system_clock::time_point start;
		float max_fps;
		float interval;

		float sleep_time = 0;
	};
}

//#include <uv.h>
//namespace kengine
//{
//	class Time
//	{
//	public:
//		float elapsed;
//		double now;
//		uint64 frame_count;
//
//		int m_fps;
//
//		void init()
//		{
//			max_fps = 60;
//			interval = 1000000000.0 / max_fps;
//			start = uv_hrtime();
//			last = start;
//		}
//		void update()
//		{
//			frame_count++;
//			auto now_time = uv_hrtime();
//			elapsed = now_time - last;
//
//			last = now_time;
//			m_fps = (int)(1000000000.0 / elapsed);
//			//if (elapsed < interval)
//			//{
//			//	uint32 sleep = (interval - elapsed) / 1000000.0f;
//			//	uv_sleep(sleep);
//			//}
//			//else {
//			//	uv_sleep(5);
//			//}
//		}
//
//		int fps() {
//			return m_fps;
//		}
//			
//
//	private:
//		uint64 last;
//		uint64 start;
//		int max_fps;
//		uint64 interval;
//	};
//}



