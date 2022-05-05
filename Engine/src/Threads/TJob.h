#pragma once

#include "../Events/Experimental/FObject.h"

namespace t3d
{
	template<typename T>
	class TJob
	{
	public:

		using Callback_Type = void(*) (FObject Instance, const T&);

		template<class C>
		TJob(C* Instance, Callback_Type Callback, T Data)
			:
			Callback (Callback),
			Data     (Data)
		{
			this->Instance.Set<C>(Instance);
		}

		void Perform()
		{
			(*Callback) (Instance, Data);
		}

	private:

		FObject       Instance;
		Callback_Type Callback;
		T             Data;
	};
}