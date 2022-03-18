#pragma once

namespace t3d
{
	template<typename T>
	struct TTypeID
	{
		T3D_INLINE static uint64 T3D_CALL GetID() { return reinterpret_cast<uint64>(typeid(T).name()); }
	};
}