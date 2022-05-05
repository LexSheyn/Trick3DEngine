#pragma once

#include "TJob.h"

namespace t3d
{
	template<typename T>
	class TWorkerThread
	{
	public:

	// Constructors and Destructor:

		TWorkerThread()
			:
			SleepDuration(33),
			ShouldStop(false)
		{
			 SEvent::ApplicationClose.Subscribe(this, OnApplicationClose);
			 SEvent::WindowClose.Subscribe(this, OnWindowClose);
		}

		~TWorkerThread()
		{
			SEvent::ApplicationClose.Unsubscribe(OnApplicationClose);
			SEvent::WindowClose.Unsubscribe(OnWindowClose);
		}

	// Functions:

		T3D_INLINE void Launch()
		{
			ShouldStop = false;

			std::thread Thread(&TWorkerThread::Run, this);

			Thread.detach();
		}

		T3D_INLINE void Stop()
		{
			ShouldStop = true;
		}

		T3D_INLINE void ScheduleJob(TJob<T> Job)
		{
			Jobs.push_back(Job);
		}

	// Accessors:

		T3D_INLINE const int32& GetSleepDuration()
		{
			return SleepDuration;
		}

	// Modifiers:

		T3D_INLINE void SetSleepDuration(int32 Duration)
		{
			SleepDuration = Duration;
		}

	private:

	// Private Functions:

		T3D_INLINE void Sleep()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(SleepDuration));
		}

		T3D_INLINE void Run()
		{
			while (ShouldStop == false)
			{
				while ( (Jobs.empty() == false) && (ShouldStop == false) )
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

		static T3D_INLINE bool8 T3D_CALL OnApplicationClose(FObject Instance, const FApplicationData& Data)
		{
			Instance.Get<TWorkerThread>()->Stop();

			return true;
		}

		static T3D_INLINE bool8 T3D_CALL OnWindowClose(FObject Instance, const FWindowData& Data)
		{
			Instance.Get<TWorkerThread>()->Stop();

			return true;
		}

		int32              SleepDuration;
		bool8              ShouldStop;
		std::list<TJob<T>> Jobs;
		std::mutex         JobMutex;
		std::mutex         SleepMutex;
	};
}