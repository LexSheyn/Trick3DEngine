#pragma once

namespace t3d
{
	template<typename T>
	struct TTypeID
	{
		static uint64 T3D_CALL GetID() { return reinterpret_cast<uint64>(typeid(T).name()); }
	};

	#define AUTO_STRING(s) std::string s = #s
}