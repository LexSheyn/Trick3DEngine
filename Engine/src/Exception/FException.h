#pragma once

namespace t3d
{
	class FException : public std::exception
	{
	public:

	// Constructor:

		FException(const std::string& File, int32 Line) noexcept;

	// Functions:

		const char8* what() const noexcept override;

	// Accessors:

		virtual const char8*       GetType()         const noexcept;

		        const std::string& GetFile()         const noexcept;

		        const int32&       GetLine()         const noexcept;

		              std::string  GetOriginString() const noexcept;

	protected:

	// Protected Variables:

		mutable std::string WhatBuffer;

	private:

	// Variables:

		std::string File;

		int32 Line;
	};
}