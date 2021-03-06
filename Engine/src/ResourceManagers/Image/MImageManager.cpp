#include "../../PCH/t3dpch.h"
#include "MImageManager.h"

#include "../../ThirdParty/stb_image.h"

namespace t3d
{
// Functions:

	FImagePNG MImageManager::LoadImage(const std::string& FilePath)
	{
		FImagePNG Image{};

		Image.Pixels = stbi_load(FilePath.c_str(), &Image.Width, &Image.Height, &Image.Channels, STBI_rgb_alpha);

		if (!Image.Pixels)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, std::string("Failed to load image: " + FilePath).c_str() });

			return FImagePNG();
		}

		return Image;
	}

}