#pragma once

namespace t3d
{
	template<typename T>
	class TImage
	{
	public:

	// Accessor:

		      T& Data()       { return Image; }

		const T& Data() const { return Image; }

	private:

	// Variable:

		T Image;
	};
}