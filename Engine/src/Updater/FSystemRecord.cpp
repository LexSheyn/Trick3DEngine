#include "../PCH/t3dpch.h"
#include "FSystemRecord.h"

namespace t3d
{
// Constructors and Destructor:

	FSystemRecord::FSystemRecord(ISystem* System, Callback_Type UpdateCallback, Callback_Type FixedUpdateCallback, Callback_Type LateUpdateCallback)
		:
		System              (System),
		UpdateCallback      (UpdateCallback),
		FixedUpdateCallback (FixedUpdateCallback),
		LateUpdateCallback( LateUpdateCallback)
	{
	}

	FSystemRecord::~FSystemRecord()
	{
	}


// Functions:

	void FSystemRecord::InvokeUpdate()
	{
		(System->*UpdateCallback) ();
	}

	void FSystemRecord::InvokeFixedUpdate()
	{
		(System->*FixedUpdateCallback) ();
	}

	void FSystemRecord::InvokeLateUpdate()
	{
		(System->*LateUpdateCallback) ();
	}

	bool8 FSystemRecord::IsEqual(ISystem* System)
	{
		return this->System == System;
	}


}