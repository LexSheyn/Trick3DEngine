#pragma once

#include "TJob.h"
#include "../Events/Experimental/SEvent.h"

namespace t3d
{
	template<typename T>
	class TWorkerThread
	{
	public:

	// Constructors and Destructor:

		TWorkerThread()
			:
			SleepDuration (33),
			b_ShouldStop  (false),
			b_Running     (false)
		{
			 SEvent::ApplicationClose.Subscribe(this, OnApplicationClose);
			 SEvent::WindowClose.Subscribe(this, OnWindowClose);
		}

		~TWorkerThread()
		{
			this->Stop();

			SEvent::ApplicationClose.Unsubscribe(OnApplicationClose);
			SEvent::WindowClose.Unsubscribe(OnWindowClose);
		}

	// Functions:

		void Launch()
		{
			b_ShouldStop = false;
			b_Running    = true;

			std::thread Thread(&TWorkerThread::Run, this);

			Thread.detach();
		}

		void Stop()
		{
			b_ShouldStop = true;
			b_Running    = false;
		}

		void ScheduleJob(TJob<T> Job)
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
			std::this_thread::sleep_for(std::chrono::milliseconds(SleepDuration));
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

	// Event Callbacks:

		static bool8 T3D_CALL OnApplicationClose(FObject Instance, const FApplicationData& Data)
		{
			Instance.Get<TWorkerThread>()->Stop();

			return true;
		}

		static bool8 T3D_CALL OnWindowClose(FObject Instance, const FWindowData& Data)
		{
			Instance.Get<TWorkerThread>()->Stop();

			return true;
		}


		std::list<TJob<T>> Jobs;
		std::mutex         JobMutex;
		std::mutex         SleepMutex;

		int32 SleepDuration;
		bool8 b_ShouldStop;
		bool8 b_Running;
	};
}