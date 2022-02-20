#pragma once

#include "Macros.h"
#include "../Types/Types.h"

namespace t3d
{
	template<typename T>
	class TScopedPointer
	{
	public:

	// Constructors and Destructor:

		TScopedPointer()           : Pointer(nullptr) {}

		TScopedPointer(T* Pointer) : Pointer(Pointer) {}

		TScopedPointer(TScopedPointer&& DyingObject)
		{
			Pointer = DyingObject.Pointer;

			DyingObject.Pointer = nullptr;
		}

		TScopedPointer(const TScopedPointer&) = delete;

		~TScopedPointer()
		{
			this->ClearMemory();
		}

	// Accessors:

		T3D_INLINE       T* Get()       { return Pointer; }

		T3D_INLINE const T* Get() const { return Pointer; }

	// Operators:

		void operator=(TScopedPointer&& DyingObject)
		{
			this->ClearMemory();

			Pointer = DyingObject.Pointer;

			DyingObject.Pointer = nullptr;
		}

		T3D_INLINE T* operator->() { return Pointer; }

		T3D_INLINE T& operator*()  { return *Pointer; }

		TScopedPointer& operator=(const TScopedPointer&) = delete;

	private:

	// Private Functions:

		void ClearMemory()
		{
			if (Pointer)
			{
				delete Pointer;
			}
		}

	// Variables:

		T* Pointer;
	};

	template<class T, typename... Types>
	[[nodiscard]] TScopedPointer<T> MakeScoped(Types&&... Args)
	{
		return TScopedPointer<T>(new T(static_cast<Types&&>(Args)...));
	}

	// In development.
	template<typename T>
	class TScopedPointer<T[]>
	{
	public:

	// Constructors and Destructor:

		TScopedPointer()           : Pointer(nullptr) {}

		TScopedPointer(T* Pointer) : Pointer(Pointer) {}

		TScopedPointer(TScopedPointer&& DyingObject)
		{
			Pointer = DyingObject.Pointer;

			DyingObject.Pointer = nullptr;
		}

		TScopedPointer(const TScopedPointer&) = delete;

		~TScopedPointer()
		{
			this->ClearMemory();
		}

	// Accessors:

		T3D_INLINE       T* Get()       { return Pointer; }

		T3D_INLINE const T* Get() const { return Pointer; }

	// Operators:

		void operator=(TScopedPointer&& DyingObject)
		{
			this->ClearMemory();

			Pointer = DyingObject.Pointer;

			DyingObject.Pointer = nullptr;
		}

		T3D_INLINE T* operator->()             { return Pointer; }

		T3D_INLINE T& operator*()              { return *Pointer; }

		T3D_INLINE T& operator[](uint32 Index) { return Pointer[Index]; } // No bounds check.

		TScopedPointer& operator=(const TScopedPointer&) = delete;

	private:

	// Private Functions:

		void ClearMemory()
		{
			if (Pointer)
			{
				delete[] Pointer;
			}
		}

	// Variables:

		T* Pointer;
	};

//#include <memory>
//
//	template <class _Ty, enable_if_t<is_array_v<_Ty>&& extent_v<_Ty> == 0, int> = 0>
//	_NODISCARD unique_ptr<_Ty> make_unique(const size_t _Size) { // make a unique_ptr
//		using _Elem = remove_extent_t<_Ty>;
//		return unique_ptr<_Ty>(new _Elem[_Size]());
//
//	template<class T, typename... Types>
//	[[nodiscard]] TScopedPointer<T> MakeScoped(Types&&... Args)
//	{
//		return TScopedPointer<T>(new T(static_cast<Types&&>(Args)...));
//	}
}