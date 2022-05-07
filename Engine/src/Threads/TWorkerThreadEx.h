#pragma once

#include "TJobEx.h"

namespace t3d
{
	template<class C, typename T>
	class TWorkerThreadEx
	{
	public:

	// Constructors and Destructor:

		TWorkerThreadEx()
			:
			SleepDuration (33),
			b_ShouldStop  (false),
			b_Running     (false)
		{
		}

		~TWorkerThreadEx()
		{
			this->StopAndFinish();
		}

	// Functions:

		void Launch()
		{
			if (b_Running == false)
			{
				b_Running    = true;
				b_ShouldStop = false;				

				Thread = std::thread{ &TWorkerThreadEx::Run, this };
			}
		}

		void Stop()
		{
			if (b_Running)
			{
				b_Running    = false;
				b_ShouldStop = true;

				Thread.join();
			}
		}

		void ScheduleJob(TJobEx<C, T> Job)
		{
			Jobs.push_back(Job);
		}

	// Accessors:

		bool8 IsRunning()
		{
			return b_Running;
		}

		const int32& GetSleepDuration()
		{
			return SleepDuration;
		}

	// Modifiers:

		void SetSleepDuration(int32 Duration)
		{
			SleepDuration = Duration;
		}

	private:

	// Private Functions:

		void Sleep()
		{
			SleepMutex.lock();

			if (b_ShouldStop == false)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(SleepDuration));
			}

			SleepMutex.unlock();
		}

		void Run()
		{
			while (b_ShouldStop == false)
			{
				while ( (Jobs.empty() == false) && (b_ShouldStop == false) )
				{
					JobMutex.lock();

					Jobs.front().Perform();
					Jobs.pop_front();

					JobMutex.unlock();
				}

				this->Sleep();
			}
		}

		void StopAndFinish()
		{
			this->Stop();

			while (Jobs.empty() == false)
			{
				Jobs.front().Perform();
				Jobs.pop_front();
			}
		}

		std::list<TJobEx<C, T>> Jobs;
		std::mutex              JobMutex;
		std::mutex              SleepMutex;

		std::thread Thread;

		int32 SleepDuration;
		bool8 b_ShouldStop;
		bool8 b_Running;
	};
}