#pragma once

namespace t3d
{
	template<typename T, typename... Rest>
	void HashCombine(uint64& Seed, const T& Structure, const Rest&... Variables)
	{
		Seed ^= std::hash<T>{}(Structure) + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);

		(HashCombine(Seed, Variables), ...);
	};
}