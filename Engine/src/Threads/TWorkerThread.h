#pragma once

#include "TJob.h"

namespace t3d
{
	template<class C, typename T>
	class TWorkerThread
	{
	public:

	// Constructors and Destructor:

		TWorkerThread()
			:
			SleepDuration (33),
			b_Running     (false)
		{
		}

		~TWorkerThread()
		{
			this->StopAndFinish();
		}

	// Functions:

		void Launch()
		{
			if (b_Running == false)
			{
				b_Running = true;			

				Thread = std::thread{ &TWorkerThread::Run, this };
			}
		}

		void Stop()
		{
			if (b_Running)
			{
				b_Running = false;

				Thread.join();
			}
		}

		void ScheduleJob(TJob<C, T> Job)
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

			if (b_Running)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(SleepDuration));
			}

			SleepMutex.unlock();
		}

		void Run()
		{
			while (b_Running)
			{
				while ( (Jobs.empty() == false) && (b_Running) )
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

		std::list<TJob<C, T>> Jobs;
		std::mutex            JobMutex;
		std::mutex            SleepMutex;

		std::thread Thread;

		bool8 b_Running;
		int32 SleepDuration;		
	};
}