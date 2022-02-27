#pragma once

namespace t3d
{
	class FTime
	{
	public:

	// Constructor:

		constexpr FTime() : Microseconds(0) {}

	// Accessors:

		T3D_INLINE constexpr float32 AsSeconds()      const { return static_cast<float32>(Microseconds / 1'000'000.0f); }

		T3D_INLINE constexpr int32   AsMilliseconds() const { return static_cast<int32>(Microseconds / 1'000); }
		
		T3D_INLINE constexpr int64   AsMicroseconds() const { return Microseconds; }

	private:

	// Private Constructor:

		constexpr explicit FTime(uint64 Microseconds) : Microseconds(Microseconds) {}

	// Variables:

		int64 Microseconds;

	// Friend Functions:

		friend constexpr FTime Seconds(float32);

		friend constexpr FTime Milliseconds(int32);
		
		friend constexpr FTime Microseconds(int64);
	};

// Functions:

	T3D_INLINE [[nodiscard]] constexpr FTime Seconds(float32 Value)    { return FTime(static_cast<int64>(Value * 1'000'000.0f)); }
	
	T3D_INLINE [[nodiscard]] constexpr FTime Milliseconds(int32 Value) { return FTime(static_cast<int64>(Value * 1'000)); }
	
	T3D_INLINE [[nodiscard]] constexpr FTime Microseconds(int64 Value) { return FTime(Value); }

// Operators:

	// Comparison.

	T3D_INLINE [[nodiscard]] constexpr bool8 operator == (FTime Left, FTime Right) { return Left.AsMicroseconds() == Right.AsMicroseconds(); }

	T3D_INLINE [[nodiscard]] constexpr bool8 operator != (FTime Left, FTime Right) { return Left.AsMicroseconds() != Right.AsMicroseconds(); }

	T3D_INLINE [[nodiscard]] constexpr bool8 operator <  (FTime Left, FTime Right) { return Left.AsMilliseconds() <  Right.AsMilliseconds(); }

	T3D_INLINE [[nodiscard]] constexpr bool8 operator >  (FTime Left, FTime Right) { return Left.AsMilliseconds() >  Right.AsMilliseconds(); }

	T3D_INLINE [[nodiscard]] constexpr bool8 operator <= (FTime Left, FTime Right) { return Left.AsMilliseconds() <= Right.AsMilliseconds(); }

	T3D_INLINE [[nodiscard]] constexpr bool8 operator >= (FTime Left, FTime Right) { return Left.AsMilliseconds() >= Right.AsMilliseconds(); }

	// -

	T3D_INLINE [[nodiscard]] constexpr FTime  operator -  (FTime Right)              { return Microseconds(-Right.AsMicroseconds()); }

	T3D_INLINE [[nodiscard]] constexpr FTime  operator -  (FTime Left, FTime Right)  { return Microseconds(Left.AsMicroseconds() - Right.AsMicroseconds()); }

	T3D_INLINE [[nodiscard]] constexpr FTime& operator -= (FTime& Left, FTime Right) { return Left = Microseconds(Left.AsMicroseconds() - Right.AsMicroseconds()); }

	// +

	T3D_INLINE [[nodiscard]] constexpr FTime  operator +  (FTime Left, FTime Right)  { return Microseconds(Left.AsMicroseconds() + Right.AsMicroseconds()); }

	T3D_INLINE [[nodiscard]] constexpr FTime& operator += (FTime& Left, FTime Right) { return Left = Microseconds(Left.AsMicroseconds() + Right.AsMicroseconds()); }

	// *
	
	T3D_INLINE [[nodiscard]] constexpr FTime  operator *  (FTime Left, float32 Right)  { return Seconds(Left.AsSeconds() * Right); }
	
	T3D_INLINE [[nodiscard]] constexpr FTime  operator *  (FTime Left, int64   Right)  { return Microseconds(Left.AsMicroseconds() * Right); }
	
	T3D_INLINE [[nodiscard]] constexpr FTime  operator *  (float32 Left, FTime Right)  { return Seconds(Left * Right.AsSeconds()); }
	
	T3D_INLINE [[nodiscard]] constexpr FTime  operator *  (int64   Left, FTime Right)  { return Microseconds(Left * Right.AsMicroseconds()); }

	T3D_INLINE [[nodiscard]] constexpr FTime& operator *= (FTime& Left, float32 Right) { return Left = Seconds(Left.AsSeconds() * Right); }
	
	T3D_INLINE [[nodiscard]] constexpr FTime& operator *= (FTime& Left, int64   Right) { return Left = Microseconds(Left.AsMicroseconds() * Right); }

	// /

	T3D_INLINE [[nodiscard]] constexpr float32 operator /  (FTime Left, FTime   Right)  { return Left.AsSeconds() / Right.AsSeconds(); }

	T3D_INLINE [[nodiscard]] constexpr FTime   operator /  (FTime Left, float32 Right)  { return Seconds(Left.AsSeconds() / Right); }

	T3D_INLINE [[nodiscard]] constexpr FTime   operator /  (FTime Left, int64   Right)  { return Microseconds(Left.AsMicroseconds() / Right); }

	T3D_INLINE [[nodiscard]] constexpr FTime&  operator /= (FTime& Left, float32 Right) { return Left = Seconds(Left.AsSeconds() / Right); }

	T3D_INLINE [[nodiscard]] constexpr FTime&  operator /= (FTime& Left, int64   Right) { return Left = Microseconds(Left.AsMicroseconds() / Right); }

	// %

	T3D_INLINE [[nodiscard]] constexpr FTime  operator %  (FTime  Left, FTime Right) { return Microseconds(Left.AsMicroseconds() % Right.AsMicroseconds()); }
	
	T3D_INLINE [[nodiscard]] constexpr FTime& operator %= (FTime& Left, FTime Right) { return Left = Microseconds(Left.AsMicroseconds() % Right.AsMicroseconds()); }
}