#pragma once

namespace t3d
{
	enum class EEventCategory : uint32
	{
		None        = 0,
		Window      = 1 << 0,
		Input       = 1 << 1,
		Keyboard    = 1 << 2,
		Mouse       = 1 << 3,
		Gamepad     = 1 << 4,
		Application = 1 << 5,
		Gameplay    = 1 << 6
	};

//	struct FEventCategory
//	{
//		static const int32 None        = 0;
//		static const int32 Application = 1;
//		static const int32 Input       = 2;
//		static const int32 Keyboard    = 3;
//		static const int32 Mouse       = 4;
//		static const int32 Gamepad     = 5;
//	};
}