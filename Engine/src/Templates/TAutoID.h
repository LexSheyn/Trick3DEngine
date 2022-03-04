#pragma once

namespace t3d
{
	template<typename T>
	class TAutoID
	{
	public:

		T3D_INLINE static const T NewID() { return Counter++; }

	private:

		static T Counter;
	};

	template<typename T>
	T TAutoID<T>::Counter = 0;
}