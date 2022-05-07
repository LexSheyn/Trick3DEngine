#pragma once

#include "FSystemRecord.h"

namespace t3d
{
	class FUpdaterEx
	{
	public:

	// Constructors and Destructor:

		 FUpdaterEx    ();
		~FUpdaterEx    ();

	// Functions:

		void  Register         (ISystem* System);
		void  Unregister       (ISystem* System);
		void  UnregisterAll    ();
		bool8 IsRegistered     (ISystem* System);

		void  Update            ();
		void  FixedUpdate       ();
		void  LateUpdate        ();

	// Accessors:

		const int32& GetFixedUpdateDelay();

	// Modifiers:

		void SetFixedUpdateDelay(int32 Delay);

	private:

	// Variables:

		int32 FixedUpdateDelay;

	// Callbacks:

		std::vector<FSystemRecord> SystemRecords;
	};
}