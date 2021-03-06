#pragma once

namespace t3d
{
	class FObject
	{
		using Pointer_Type = void*;

	public:

		template<class C>
		void Set(C* Instance)
		{
			this->Instance = reinterpret_cast<Pointer_Type>(Instance);
		}

		template<class C>
		C* Get()
		{
			return reinterpret_cast<C*>(Instance);
		}

		bool8 IsEmpty();

	private:

		Pointer_Type Instance;
	};
}