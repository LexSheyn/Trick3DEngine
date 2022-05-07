#pragma once

#include "FImagePNG.h"
#include "../../Events/Experimental/SEvent.h"

namespace t3d
{
	class MImageManager
	{
	public:

	// Functions:

		static FImagePNG T3D_CALL LoadImage(const std::string& FilePath);

	private:

	// Private Constructor and Destructor:

		 MImageManager() {}
		~MImageManager() {}

		T3D_NO_COPY(MImageManager);
		T3D_NO_MOVE(MImageManager);

	// Variables:

		// Storage: std::vector<uint8>
	};
}