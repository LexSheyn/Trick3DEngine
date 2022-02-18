#include "../PrecompiledHeaders/t3dpch.h"
#include "FVulkanException.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructor:

	FVulkanException::FVulkanException(const std::string& File, int32 Line, VkResult Result) noexcept
		: FException(File.c_str(), Line), Result(Result)
	{
	}


// Functions:

	const char8* FVulkanException::what() const noexcept
	{
		std::ostringstream Message;

		Message << this->GetType()
			    << "\n" << "[Error code]: 0x" << std::hex << std::uppercase << this->GetErrorCode()
			    << std::dec << " (" << static_cast<uint64>(this->GetErrorCode()) << ")"
			    << "\n" << "[Error string]: " << this->GetErrorString()
			    << "\n" << "[Description]: " << this->GetErrorDescription()
			    << "\n" << this->GetOriginString();

		WhatBuffer = Message.str();

		return WhatBuffer.c_str();
	}


// Accessors:

	const char8* FVulkanException::GetType() const noexcept
	{
		return "[ Vulkan Exception ]";
	}

	const VkResult& FVulkanException::GetErrorCode() const noexcept
	{
		return Result;
	}

	std::string FVulkanException::GetErrorString() const noexcept
	{
		return std::string("None");
	}

	std::string FVulkanException::GetErrorDescription() const noexcept
	{
		return std::string("None");
	}

}

#pragma warning( pop ) // Vulkan SDK - End