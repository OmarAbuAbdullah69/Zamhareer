#include <chrono>

#ifndef OAA_TIMER_H
#define OAA_TIMER_H
namespace OAA
{
	class Timer
	{
		public:
			Timer();
			void Reset();
			double GetTime();
		private:
			std::chrono::high_resolution_clock::time_point m_StartTime;
	};

#ifdef OAA_TIMER_IMPL
	Timer::Timer()
	{
		Reset();
	}
	void Timer::Reset()
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
	}
	double Timer::GetTime()
	{
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = currentTime - m_StartTime;
        return duration.count();
	}
#endif //OAA_TIMER_IMPL
}



#endif //OAA_TIMER_H


