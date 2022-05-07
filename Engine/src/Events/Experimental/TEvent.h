#pragma once

#include "TDelegate.h"

namespace t3d
{
	template<typename T>
	class TEvent
	{
	public:
		
		template<class C>
		void Subscribe(C* Instance, TDelegate<T>::Callback_Type Callback)
		{
			Delegates.push_back(TDelegate<T>(Instance, Callback));
		}

		void Unsubscribe(TDelegate<T>::Callback_Type Callback)
		{
			for (size_t i = 0u; i < Delegates.size(); i++)
			{
				if (Delegates.at(i).IsEqual(Callback))
				{
					Delegates.at(i) = Delegates.back();

					Delegates.pop_back();

					return;
				}
			}
		}

		bool8 IsSubscribed(TDelegate<T>::Callback_Type Callback)
		{
			for (auto& Delegate : Delegates)
			{
				if (Delegate.IsEqual(Callback))
				{
					return true;
				}
			}

			return false;
		}

		void Invoke(const T& Data)
		{
			for (auto& Delegate : Delegates)
			{
				if (Delegate.Invoke(Data) == false)
				{
					return;
				}
			}
		}

	private:

		std::vector<TDelegate<T>> Delegates;
	};
}