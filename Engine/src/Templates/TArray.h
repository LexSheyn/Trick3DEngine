#pragma once

namespace t3d
{
	template<typename T, uint64 S>
	class TArray
	{
	public:
	
	// Accessors:
	
		constexpr uint64 Size() const { return S; }
	
		      T* Data()       { return Array; }
	
		const T* Data() const { return Array; }
	
	// Operators:
	
		      T& operator [] (uint64 Index)       { return Array[Index]; }
	
		const T& operator [] (uint64 Index) const { return Array[Index]; }
	
		      T& operator [] (enum class ESound Index)       { return Array[static_cast<uint64>(Index)]; }

		const T& operator [] (enum class ESound Index) const { return Array[static_cast<uint64>(Index)]; }

		      T& operator [] (enum class ESoundGroup Index)       { return Array[static_cast<uint64>(Index)]; }

		const T& operator [] (enum class ESoundGroup Index) const { return Array[static_cast<uint64>(Index)]; }
	
	private:
	
	// Variables:
	
		T Array[S];
	};
}