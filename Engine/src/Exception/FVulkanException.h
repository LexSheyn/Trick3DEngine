#pragma once

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

#include "FException.h"

namespace t3d
{
	class FVulkanException : public FException
	{
	public:

	// Constructor:

		FVulkanException(const std::string& File, int32 Line, VkResult Result) noexcept;

	// Functions:

		const char8* what() const noexcept override;

	// Accessors:

		const char8*      GetType()             const noexcept override;

		const VkResult&   GetErrorCode()        const noexcept;

		      std::string GetErrorString()      const noexcept;

		      std::string GetErrorDescription() const noexcept;

	private:

	// Variables:

		VkResult Result;

		std::string Info;
	};

#define VULKAN_EXCEPTION(Result) FVulkanException(__FILE__, __LINE__, Result)
}

#pragma warning( pop ) // Vulkan SDK - End