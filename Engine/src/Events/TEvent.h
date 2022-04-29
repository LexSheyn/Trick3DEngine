#pragma once

#include "TDelegate.h"

namespace t3d
{
	template<typename T>
	class TEvent
	{
	public:

		void Subscribe(void (*Callback) (const T&))
		{
			Delegates.push_back(TDelegate<T>{ Callback });
		}

		void Unsubscribe(void (*Callback) (const T&))
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

		bool8 IsSubscribed(void (*Callback) (const T&))
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
				(*Delegate.Callback) (Data);
			}
		}

	private:

		std::vector<TDelegate<T>> Delegates;
	};

	template<typename T>
	void operator += (TEvent<T>& Event, void (*Callback) (const T&))
	{
		Event.Subscribe(Callback);
	}

	template<typename T>
	void operator -= (TEvent<T>& Event, void (*Callback) (const T&))
	{
		Event.Unsubscribe(Callback);
	}
}