#include "../PCH/t3dpch.h"
#include "FTimeStamp.h"

namespace t3d
{
// Functions:

	std::string FTimeStamp::GetAsString()
	{
		std::time_t CurrentCalendarTime = std::time(nullptr);

		std::tm LocalTime{};

		char8 TimeAsCharArray[9]{}; // HH:MM:SS, 9 chars: 8 for numbers + 1 for '\0' (null terminator).

		localtime_s(&LocalTime, &CurrentCalendarTime);

		std::strftime(TimeAsCharArray, sizeof(TimeAsCharArray), "%H:%M:%S", &LocalTime);

		return std::string(TimeAsCharArray);
	}

}