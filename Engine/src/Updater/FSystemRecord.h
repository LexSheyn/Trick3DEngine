#pragma once

#include "../ECS/Systems/ISystem.h"

namespace t3d
{
	class FSystemRecord
	{
	public:

		using Callback_Type = void(ISystem::*) ();

	// Constructors and Destructor:

		 FSystemRecord    (ISystem* System, Callback_Type UpdateCallback, Callback_Type FixedUpdateCallback, Callback_Type LateUpdateCallback);
		~FSystemRecord    ();

	// Functions:

		void  InvokeUpdate         ();
		void  InvokeFixedUpdate    ();
		void  InvokeLateUpdate     ();
		bool8 IsEqual              (ISystem* System);

	private:

	// Variables:

		ISystem*      System;
		Callback_Type UpdateCallback;
		Callback_Type FixedUpdateCallback;
		Callback_Type LateUpdateCallback;
	};
}