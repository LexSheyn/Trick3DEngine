#include "../PCH/t3dpch.h"
#include "FTimeStamp.h"

namespace t3d
{
// Constructor:

	FTimeStamp::FTimeStamp()
	{
		std::time_t CurrentCalendarTime = std::time(nullptr);

		std::tm LocalTime{};

		localtime_s(&LocalTime, &CurrentCalendarTime);

		std::strftime(TimeAsCharArray, sizeof(TimeAsCharArray), "%H:%M:%S", &LocalTime);
	}

	char8* FTimeStamp::Get()
	{
		return TimeAsCharArray;
	}

	std::string FTimeStamp::GetAsString()
	{
		return std::string(TimeAsCharArray);
	}

}