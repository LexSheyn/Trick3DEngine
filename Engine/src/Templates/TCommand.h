#pragma once

namespace t3d
{
	class FClass
	{};

	struct FData
	{};

	template<typename T>
	class TCallback
	{
	public:

		template<class C>
		void Bind(C* Instance, void (C::*Callback) (const T&))
		{
			Command = std::bind(Callback, Instance, std::placeholders::_1);
		}

		void Invoke(const T& Data)
		{
			if (Command)
			{
				std::invoke(Command, Data);
			}
		}

	private:

		std::function<void(const T&)> Command;
	};

	template<class C>
	struct ICommand
	{
		virtual void Execute(C* Instance) = 0;
	};

//	template<class C>
//	struct FCommandNull : ICommand<C>
//	{
//		T3D_INLINE void Execute(C* Instance) override {}
//	};

//	struct FCommandFire : ICommand
//	{
//		T3D_INLINE void Execute(FClass* Instance) override
//		{
//
//		}
//	};
}