#pragma once

#include "../ECS/Systems/ISystem.h"

namespace t3d
{
	class FSystemCallback
	{
	public:

		using Callback_Type = void(ISystem::*) ();

	// Constructors and Destructor:

		 FSystemCallback    (ISystem* System, Callback_Type Callback);
		~FSystemCallback    ();

	// Functions:

	//	void  Bind       (ISystem* Instance, Callback_Type Callback);
		void  Invoke     ();
		bool8 IsEqual    (ISystem* System);
		bool8 IsEqual    (Callback_Type Callback);
	//	bool8 IsEmpty    ();

	private:

	// Variables:

		ISystem*      System;
		Callback_Type Callback;
	};
}