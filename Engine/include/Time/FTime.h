#pragma once

namespace t3d
{
	class FTime
	{
	public:

	// Constructor:

		FTime();

	// Functions:

		static const FTime Seconds(float32 Value);

		static const FTime Milliseconds(int32 Value);
		
		static const FTime Microseconds(int64 Value);

	// Accessors:

		const float32 AsSeconds()      const;

		const int32   AsMilliseconds() const;
		
		const int64   AsMicroseconds() const;

	private:

	// Private Constructor:

		explicit FTime(uint64 Microseconds);

	// Variables:

		int64 TimeInMicroseconds;
	};

// Operators:

	// Comparison.

	T3D_NO_DISCARD const bool8 operator == (FTime Left, FTime Right);

	T3D_NO_DISCARD const bool8 operator != (FTime Left, FTime Right);

	T3D_NO_DISCARD const bool8 operator <  (FTime Left, FTime Right);

	T3D_NO_DISCARD const bool8 operator >  (FTime Left, FTime Right);

	T3D_NO_DISCARD const bool8 operator <= (FTime Left, FTime Right);

	T3D_NO_DISCARD const bool8 operator >= (FTime Left, FTime Right);

	// -

	T3D_NO_DISCARD const FTime  operator -  (FTime  Right);

	T3D_NO_DISCARD const FTime  operator -  (FTime  Left, FTime Right);

	               const FTime& operator -= (FTime& Left, FTime Right);

	// +

	T3D_NO_DISCARD const FTime  operator +  (FTime  Left, FTime Right);

	               const FTime& operator += (FTime& Left, FTime Right);

	// *
	
	T3D_NO_DISCARD const FTime  operator *  (FTime   Left, float32 Right);
	
	T3D_NO_DISCARD const FTime  operator *  (FTime   Left, int64   Right);
	
	T3D_NO_DISCARD const FTime  operator *  (float32 Left, FTime   Right);
	
	T3D_NO_DISCARD const FTime  operator *  (int64   Left, FTime   Right);

	               const FTime& operator *= (FTime&  Left, float32 Right);
	               
	               const FTime& operator *= (FTime&  Left, int64   Right);

	// /

	T3D_NO_DISCARD const float32 operator /  (FTime  Left, FTime   Right);

	T3D_NO_DISCARD const FTime   operator /  (FTime  Left, float32 Right);

	T3D_NO_DISCARD const FTime   operator /  (FTime  Left, int64   Right);

	               const FTime&  operator /= (FTime& Left, float32 Right);
	               
	               const FTime&  operator /= (FTime& Left, int64   Right);

	// %

	T3D_NO_DISCARD const FTime  operator %  (FTime  Left, FTime Right);
	
	               const FTime& operator %= (FTime& Left, FTime Right);
}