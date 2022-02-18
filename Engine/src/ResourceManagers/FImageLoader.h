#pragma once

#include "FImagePNG.h"

namespace t3d
{
	class FImageLoader
	{
	public:

	// Functions:

		static FImagePNG LoadFromFile(const std::string& FilePath);
	};
}