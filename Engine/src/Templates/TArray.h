#pragma once

namespace t3d
{
	template<typename T, uint64 S>
	class TArray
	{
	public:

		using SizeType = uint64;
	
	// Accessors:
	
		constexpr SizeType Size    () const noexcept { return S; }	
		const T*           Data    () const          { return Array; }
		      T*           Data    ()                { return Array; }		
	
	// Operators:
	
		const T& operator [] (const SizeType Index) const { return Array[Index]; }
		      T& operator [] (const SizeType Index)       { return Array[Index]; }
	
		const T& operator [] (enum class ESound Index) const { return Array[static_cast<SizeType>(Index)]; }	
		      T& operator [] (enum class ESound Index)       { return Array[static_cast<SizeType>(Index)]; }

		const T& operator [] (enum class ESoundGroup Index) const { return Array[static_cast<SizeType>(Index)]; }
		      T& operator [] (enum class ESoundGroup Index)       { return Array[static_cast<SizeType>(Index)]; }

		const T& operator [] (enum class EScene Index) const { return Array[static_cast<SizeType>(Index)]; }
		      T& operator [] (enum class EScene Index)       { return Array[static_cast<SizeType>(Index)]; }

		const T& operator [] (enum class EShaderType Index) const { return Array[static_cast<SizeType>(Index)]; }
		      T& operator [] (enum class EShaderType Index)       { return Array[static_cast<SizeType>(Index)]; }

		const T& operator [] (enum class EEvent Index) const { return Array[static_cast<SizeType>(Index)]; }
		      T& operator [] (enum class EEvent Index)       { return Array[static_cast<SizeType>(Index)]; }
	
	private:
	
	// Variables:
	
		T Array[S];
	};
}