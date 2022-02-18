#include "../PrecompiledHeaders/t3dpch.h"
#include "FException.h"

namespace t3d
{
// Constructor:

	FException::FException(const std::string& File, int32 Line) noexcept
		: File(File), Line(Line)
	{
	}


// Fumctopms:

	const char8* FException::what() const noexcept
	{
		std::ostringstream Message;

		Message << this->GetType() << "\n"
		        << this->GetOriginString();

		WhatBuffer = Message.str();

		return WhatBuffer.c_str();
	}


// Accessors:

	const char8* FException::GetType() const noexcept
	{
		return "[ Basic Exception ]";
	}

	const std::string& FException::GetFile() const noexcept
	{
		return File;
	}

	const int32& FException::GetLine() const noexcept
	{
		return Line;
	}

	std::string FException::GetOriginString() const noexcept
	{
		std::ostringstream OriginString;

		OriginString << "[File]: " << File << "\n"
			         << "[Line]: " << Line;

		return OriginString.str();
	}

}