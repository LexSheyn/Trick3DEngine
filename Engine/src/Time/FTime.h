#pragma once

namespace t3d
{
	class FTime
	{
	public:

	// Constructor:

		FTime();

	// Functions:

		static const FTime T3D_CALL Seconds         (float32 Value);
		static const FTime T3D_CALL Milliseconds    (int32 Value);		
		static const FTime T3D_CALL Microseconds    (int64 Value);

	// Accessors:

		const float32 T3D_CALL AsSeconds         () const;
		const int32   T3D_CALL AsMilliseconds    () const;		
		const int64   T3D_CALL AsMicroseconds    () const;

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