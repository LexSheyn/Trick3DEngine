#pragma once

namespace t3d
{
	template<class C>
	class TAutoID
	{
	public:

		static constexpr uint64 GetNew()
		{
			uint64* CounterPtr = const_cast<uint64*>(&Counter);

			return *CounterPtr++;
		}

	private:

		static constexpr uint64 Counter = 0;
	};
}