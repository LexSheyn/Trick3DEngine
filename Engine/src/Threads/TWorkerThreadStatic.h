#pragma once

#include "TJobStatic.h"
#include "../Events/Experimental/SEvent.h"

namespace t3d
{
	template<typename T>
	class TWorkerThreadStatic
	{
	public:

	// Constructors and Destructor:

		TWorkerThreadStatic()
			:
			SleepDuration (33),
			b_Running     (false)
		{
		}

		~TWorkerThreadStatic()
		{
			this->StopAndFinish();
		}

	// Functions:

		void Launch()
		{
			if (b_Running == false)
			{
				b_Running = true;

				Thread = std::thread{ &TWorkerThreadStatic::Run, this };
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

		void ScheduleJob(TJobStatic<T> Job)
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

		std::list<TJobStatic<T>> Jobs;
		std::mutex               JobMutex;
		std::mutex               SleepMutex;

		std::thread Thread;

		bool8 b_Running;
		int32 SleepDuration;		
	};
}