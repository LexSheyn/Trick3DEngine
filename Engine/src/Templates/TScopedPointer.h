#pragma once

#include "../Macros/T3DMacros.h"
#include "../Types/T3DTypes.h"

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

		      T* Get()       { return Pointer; }

		const T* Get() const { return Pointer; }

	// Operators:

		void operator=(TScopedPointer&& DyingObject) noexcept
		{
			this->ClearMemory();

			Pointer = DyingObject.Pointer;

			DyingObject.Pointer = nullptr;
		}

		T* operator->() { return Pointer; }

		T& operator*()  { return *Pointer; }

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
	T3D_NO_DISCARD TScopedPointer<T> MakeScoped(Types&&... Args)
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

		      T* Get()       { return Pointer; }

		const T* Get() const { return Pointer; }

	// Operators:

		void operator=(TScopedPointer&& DyingObject) noexcept
		{
			this->ClearMemory();

			Pointer = DyingObject.Pointer;

			DyingObject.Pointer = nullptr;
		}

		T* operator->()             { return Pointer; }

		T& operator*()              { return *Pointer; }

		T& operator[](uint32 Index) { return Pointer[Index]; } // No bounds check.

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
//	_NODISCARD unique_ptr<_Ty> make_unique(const uint64 _Size) { // make a unique_ptr
//		using _Elem = remove_extent_t<_Ty>;
//		return unique_ptr<_Ty>(new _Elem[_Size]());
//
//	template<class T, typename... Types>
//	T3D_NO_DISCARD TScopedPointer<T> MakeScoped(Types&&... Args)
//	{
//		return TScopedPointer<T>(new T(static_cast<Types&&>(Args)...));
//	}
}