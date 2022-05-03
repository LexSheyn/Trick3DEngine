#pragma once

#include "TDelegate.h"

namespace t3d
{
	template<typename T>
	class TEvent
	{
	public:
		
		template<class C>
		T3D_INLINE void Subscribe(C* Instance, TDelegate<T>::Callback_Type Callback)
		{
			Delegates.push_back(TDelegate<T>());

			Delegates.back().Bind<C>(Instance, Callback);
		}

		T3D_INLINE void Unsubscribe(TDelegate<T>::Callback_Type Callback)
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

		T3D_INLINE bool8 IsSubscribed(TDelegate<T>::Callback_Type Callback)
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

		T3D_INLINE void Invoke(const T& Data)
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