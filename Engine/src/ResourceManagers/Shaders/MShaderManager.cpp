#include "../../PrecompiledHeaders/t3dpch.h"
#include "MShaderManager.h"

namespace t3d
{
// Functions:

	std::vector<char8> MShaderManager::ReadAsBinary(const std::string& FilePath)
	{
		std::ifstream InFile;

		InFile.open(FilePath, std::ios::ate | std::ios::binary);

		if (!InFile.is_open())
		{
			LOG_ERROR("Failed to open: " + FilePath);
			throw;
		}

		uint64 FileSize = static_cast<uint64>(InFile.tellg());

		std::vector<char8> Buffer(FileSize);

		InFile.seekg(0);

		InFile.read(Buffer.data(), FileSize);

		InFile.close();

		return Buffer;
	}
}