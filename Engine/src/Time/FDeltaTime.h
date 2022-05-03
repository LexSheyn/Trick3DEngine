#pragma once

namespace t3d
{
	class FDeltaTime
	{
	public:

	// Accessors:

		static const float32& T3D_CALL Get();

	private:

	// Modifiers:

		static void T3D_CALL Set(float32 Seconds);

	// Variables:

		static float32 Time;

		friend class FApplication;
	};
}