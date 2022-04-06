#pragma once

namespace t3d
{
	/*
	void* operator new(size_t Size)
	{
	// Avoid std::malloc(0) which may return nullptr on success:

		if (Size == 0u)
		{
			++Size;
		}

		void* Memory = std::malloc(Size);

		if (Memory == nullptr)
		{
			// Do something to indicate the error...

			return nullptr; // Custom version.

		//	throw std::bad_alloc(); // Default behaviour in C.
		}

		return Memory;		
	}

	void operator delete(void* Memory) noexcept
	{
		std::free(Memory);
	}
	*/
}