#pragma once

template<typename T, uint64 S>
class TArray
{
public:

// Accessors:

	constexpr uint64 Size() const { return S; }

	      T* Data()       { return Array; }

	const T* Data() const { return Array; }

// Operators:

	      T& operator[] (uint64 Index)       { return Array[Index]; }

	const T& operator[] (uint64 Index) const { return Array[Index]; }

private:

// Variables:

	T Array[S];
};