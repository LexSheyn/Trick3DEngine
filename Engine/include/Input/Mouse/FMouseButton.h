#pragma once

namespace t3d
{
	class FMouseButton
	{
		// From glfw3.h
		static constexpr int32 Button_1          = 0;
		static constexpr int32 Button_2          = 1;
		static constexpr int32 Button_3          = 2;
		static constexpr int32 Button_4          = 3;
		static constexpr int32 Button_5          = 4;
		static constexpr int32 Button_6          = 5;
		static constexpr int32 Button_7          = 6;
		static constexpr int32 Button_8          = 7;
		static constexpr int32 Left       = Button_1;
		static constexpr int32 Right      = Button_2;
		static constexpr int32 Middle     = Button_3;
		static constexpr int32 Last       = Button_8;
	};
}