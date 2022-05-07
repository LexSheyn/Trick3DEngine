#pragma once

namespace t3d
{
	class FTimeStamp
	{
	public:

		FTimeStamp();

		/// <returns> Current time as char8* in HH:MM:SS format. </returns>
		char8* Get();
		
		/// <returns> Current time as std::string in HH:MM:SS format. </returns>
		std::string GetAsString();

	private:

		// HH:MM:SS, 9 chars: 8 for numbers + 1 for '\0' (null terminator).
		char8 TimeAsCharArray[9];
	};
}