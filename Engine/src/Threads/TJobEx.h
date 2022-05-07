#pragma once

namespace t3d
{
	template<class C, typename T>
	class TJobEx
	{
	public:

		using Callback_Type = void(C::*) (T);

		TJobEx(C* Instance, Callback_Type Callback, T Data)
			:
			Instance (Instance),
			Callback (Callback),
			Data     (Data)
		{
		}

		void Perform()
		{
			(*Instance.*Callback) (Data);
		}

	private:

		C*            Instance;
		Callback_Type Callback;
		T             Data;
	};
}