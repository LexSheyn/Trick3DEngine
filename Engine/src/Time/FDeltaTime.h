#pragma once

namespace t3d
{
	class FDeltaTime
	{
	public:

	// Accessors:

		static const float32& T3D_CALL Get();

	// Modifiers:

		static void T3D_CALL Set(float32 Seconds);

	private:

	// Variables:

		static float32 Time;
	};
}