#include "../PrecompiledHeaders/t3dpch.h"
#include "FTime.h"

namespace t3d
{
// Constructor:

	FTime::FTime()
		: TimeInMicroseconds(0)
	{
	}


// Functions:

	const FTime FTime::Seconds(float32 Value)
	{
		return FTime(static_cast<int64>(Value * 1'000'000.0f));
	}

	const FTime FTime::Milliseconds(int32 Value)
	{
		return FTime(static_cast<int64>(Value * 1'000));
	}

	const FTime FTime::Microseconds(int64 Value)
	{
		return FTime(Value);
	}


// Accessors:

	const float32 FTime::AsSeconds() const
	{
		return static_cast<float32>(TimeInMicroseconds / 1'000'000.0f);
	}

	const int32 FTime::AsMilliseconds() const
	{
		return static_cast<int32>(TimeInMicroseconds / 1'000);
	}

	const int64 FTime::AsMicroseconds() const
	{
		return TimeInMicroseconds;
	}


// Private Constructor:

	FTime::FTime(uint64 Microseconds)
		: TimeInMicroseconds(Microseconds)
	{
	}


// Operator:

	const bool8 operator==(FTime Left, FTime Right)
	{
		return Left.AsMicroseconds() == Right.AsMicroseconds();
	}

	const bool8 operator!=(FTime Left, FTime Right)
	{
		return Left.AsMicroseconds() != Right.AsMicroseconds();
	}

	const bool8 operator<(FTime Left, FTime Right)
	{
		return Left.AsMilliseconds() < Right.AsMilliseconds();
	}

	const bool8 operator>(FTime Left, FTime Right)
	{
		return Left.AsMilliseconds() > Right.AsMilliseconds();
	}

	const bool8 operator<=(FTime Left, FTime Right)
	{
		return Left.AsMilliseconds() <= Right.AsMilliseconds();
	}

	const bool8 operator>=(FTime Left, FTime Right)
	{
		return Left.AsMilliseconds() >= Right.AsMilliseconds();
	}

	const FTime operator-(FTime Right)
	{
		return FTime::Microseconds(-Right.AsMicroseconds());
	}

	const FTime operator-(FTime Left, FTime Right)
	{
		return FTime::Microseconds(Left.AsMicroseconds() - Right.AsMicroseconds());
	}

	const FTime& operator-=(FTime& Left, FTime Right)
	{
		return Left = FTime::Microseconds(Left.AsMicroseconds() - Right.AsMicroseconds());
	}

	const FTime operator+(FTime Left, FTime Right)
	{
		return FTime::Microseconds(Left.AsMicroseconds() + Right.AsMicroseconds());
	}

	const FTime& operator+=(FTime& Left, FTime Right)
	{
		return Left = FTime::Microseconds(Left.AsMicroseconds() + Right.AsMicroseconds());
	}

	const FTime operator*(FTime Left, float32 Right)
	{
		return FTime::Seconds(Left.AsSeconds() * Right);
	}

	const FTime operator*(FTime Left, int64 Right)
	{
		return FTime::Microseconds(Left.AsMicroseconds() * Right);
	}

	const FTime operator*(float32 Left, FTime Right)
	{
		return FTime::Seconds(Left * Right.AsSeconds());
	}

	const FTime operator*(int64 Left, FTime Right)
	{
		return FTime::Microseconds(Left * Right.AsMicroseconds());
	}

	const FTime& operator*=(FTime& Left, float32 Right)
	{
		return Left = FTime::Seconds(Left.AsSeconds() * Right);
	}

	const FTime& operator*=(FTime& Left, int64 Right)
	{
		return Left = FTime::Microseconds(Left.AsMicroseconds() * Right);
	}

	const float32 operator/(FTime Left, FTime Right)
	{
		return Left.AsSeconds() / Right.AsSeconds();
	}

	const FTime operator/(FTime Left, float32 Right)
	{
		return FTime::Seconds(Left.AsSeconds() / Right);
	}

	const FTime operator/(FTime Left, int64 Right)
	{
		return FTime::Microseconds(Left.AsMicroseconds() / Right);
	}

	const FTime& operator/=(FTime& Left, float32 Right)
	{
		return Left = FTime::Seconds(Left.AsSeconds() / Right);
	}

	const FTime& operator/=(FTime& Left, int64 Right)
	{
		return Left = FTime::Microseconds(Left.AsMicroseconds() / Right);
	}

	const FTime operator%(FTime Left, FTime Right)
	{
		return FTime::Microseconds(Left.AsMicroseconds() % Right.AsMicroseconds());
	}

	const FTime& operator%=(FTime& Left, FTime Right)
	{
		return Left = FTime::Microseconds(Left.AsMicroseconds() % Right.AsMicroseconds());
	}

}