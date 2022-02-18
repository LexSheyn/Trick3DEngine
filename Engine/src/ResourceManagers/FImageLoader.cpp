#include "../PrecompiledHeaders/t3dpch.h"
#include "FImageLoader.h"

#include "../ThirdParty/stb_image.h"

namespace t3d
{
// Functions:

	FImagePNG FImageLoader::LoadFromFile(const std::string& FilePath)
	{
		FImagePNG Image{};

		Image.Pixels = stbi_load(FilePath.c_str(), &Image.Width, &Image.Height, &Image.Channels, STBI_rgb_alpha);

		if (!Image.Pixels)
		{
			LOG_ERROR("Failed to load image: " + FilePath);

			return FImagePNG();
		}

		return Image;
	}
}