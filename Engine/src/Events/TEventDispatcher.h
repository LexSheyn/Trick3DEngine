#pragma once

#include "EventCallbackTypes.h"

namespace t3d
{
	template<typename T, typename ArgT>
	class TEventDispatcher
	{
	public:

		void Subscribe(T Callback)
		{
			Callbacks.push_back(Callback);
		}

		void Unsubscribe(T Callback)
		{
			for (size_t i = 0u; i < Callbacks.size(); i++)
			{
				if (Callbacks.at(i) == Callback)
				{
					Callbacks.at(i) = Callbacks.back();

					Callbacks.pop_back();
				}
			}
		}

		void Invoke(const ArgT& Data)
		{
			for (auto& Callback : Callbacks)
			{
				(*Callback) (Data);
			}
		}

	private:

		std::vector<T> Callbacks;
	};

	template<typename T, typename ArgT>
	void operator += (TEventDispatcher<T, ArgT>& Dispatcher, T Callback)
	{
		Dispatcher.Subscribe(Callback);
	}

	template<typename T, typename ArgT>
	void operator -= (TEventDispatcher<T, ArgT>& Dispatcher, T Callback)
	{
		Dispatcher.Unsubscribe(Callback);
	}
}