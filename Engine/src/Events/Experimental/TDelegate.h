#pragma once

namespace t3d
{
	template<typename T>
	class TDelegate
	{
	public:

		using Instance_Type = void*;
		using Callback_Type = bool8(*) (Instance_Type, const T&);

		template<class C>
		void Bind(C* Instance, Callback_Type Callback)
		{
			this->Instance = reinterpret_cast<Instance_Type>(Instance);

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

		Instance_Type Instance;
		Callback_Type Callback;
	};
}