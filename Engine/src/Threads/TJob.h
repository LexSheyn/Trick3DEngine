#pragma once

namespace t3d
{
	template<class C, typename T>
	class TJob
	{
	public:

		using Callback_Type = void(C::*) (T);

		TJob(C* Instance, Callback_Type Callback, T Data)
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