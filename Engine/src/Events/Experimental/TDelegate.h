#pragma once

#include "FObject.h"

namespace t3d
{
	template<typename T>
	class TDelegate
	{
	public:

		using Callback_Type = bool8(*) (FObject, const T&);

		template<class C>
		void Bind(C* Instance, Callback_Type Callback)
		{
			this->Instance.Set<C>(Instance);

			this->Callback = Callback;
		}

		bool8 Invoke(const T& Data)
		{
			return (*Callback) (Instance, Data);
		}

		bool8 IsEqual(Callback_Type Callback)
		{
			return this->Callback == Callback;
		}

		bool8 IsEmpty()
		{
			return Callback == nullptr;
		}

	private:

		FObject       Instance;
		Callback_Type Callback;
	};
}