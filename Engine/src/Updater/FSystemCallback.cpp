#include "../PCH/t3dpch.h"
#include "FSystemCallback.h"

namespace t3d
{
// Constructors and Destructor:

	FSystemCallback::FSystemCallback(ISystem* System, Callback_Type Callback)
		:
		System   (System),
		Callback (Callback)
	{
	}

	FSystemCallback::~FSystemCallback()
	{
		System   = nullptr;
		Callback = nullptr;
	}


// Functions:

//	void FSystemCallback::Bind(ISystem* Instance, Callback_Type Callback)
//	{
//		this->Instance = Instance;
//		this->Callback = Callback;
//	}

	void FSystemCallback::Invoke()
	{
		(System->*Callback) ();
	}

	bool8 FSystemCallback::IsEqual(ISystem* System)
	{
		return this->System == System;
	}

	bool8 FSystemCallback::IsEqual(Callback_Type Callback)
	{
		return this->Callback == Callback;
	}

//	bool8 FSystemCallback::IsEmpty()
//	{
//		return (Instance == nullptr) && (Callback == nullptr);
//	}


}