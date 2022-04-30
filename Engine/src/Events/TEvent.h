#pragma once

#include "TDelegate.h"

namespace t3d
{
	template<typename T>
	class TEvent
	{
	public:

		void Subscribe(TDelegate<T>::Callback_Type Callback)
		{
			Delegates.push_back(TDelegate<T>{ Callback });
		}

		void Unsubscribe(TDelegate<T>::Callback_Type Callback)
		{
			for (size_t i = 0u; i < Delegates.size(); i++)
			{
				if (Delegates.at(i).Callback == Callback)
				{
					Delegates.at(i) = Delegates.back();

					Delegates.pop_back();
				}
			}
		}

		bool8 IsSubscribed(TDelegate<T>::Callback_Type Callback)
		{
			for (size_t i = 0u; i < Delegates.size(); i++)
			{
				if (Delegates.at(i).Callback == Callback)
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
				if ( (*Delegate.Callback) (Data) == false )
				{
					return;
				}
			}
		}

	private:

		std::vector<TDelegate<T>> Delegates;
	};

	template<typename T>
	void operator += (TEvent<T>& Event, typename TDelegate<T>::Callback_Type Callback)
	{
		Event.Subscribe(Callback);
	}

	template<typename T>
	void operator -= (TEvent<T>& Event, typename TDelegate<T>::Callback_Type Callback)
	{
		Event.Unsubscribe(Callback);
	}
}