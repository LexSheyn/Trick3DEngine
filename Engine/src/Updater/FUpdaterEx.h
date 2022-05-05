#pragma once

#include "FSystemCallback.h"

namespace t3d
{
	class FUpdaterEx
	{
	public:

	// Constructors and Destructor:

		 FUpdaterEx    ();
		~FUpdaterEx    ();

	// Functions:

		void  Subscribe         (ISystem* System);
		void  Unsubscribe       (ISystem* System);
		void  UnsubscribeAll    ();
		bool8 IsSubscribed      (ISystem* System);

		void  Update            ();
		void  FixedUpdate       ();
		void  LastUpdate        ();

	// Accessors:

		const int32& GetFixedUpdateDelay();

	// Modifiers:

		void SetFixedUpdateDelay(int32 Delay);

	private:

	// Variables:

		int32 FixedUpdateDelay;

	// Callbacks:

		std::vector<ISystem*>        Systems;
		std::vector<FSystemCallback> SystemCallbacks;
		std::vector<FSystemCallback> FixedSystemCallbacks;
		std::vector<FSystemCallback> LastSystemCallbacks;
	};
}