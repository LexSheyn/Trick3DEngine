#pragma once

namespace t3d
{	
	enum class EEventType : uint32
	{
	// Window:

		WindowClosed = 0u,
		WindowResized,
		WindowFrameBufferResized,
		WindowContentScaled,
		WindowMoved,
		WindowIconified,
		WindowMaximized,
		WindowFocused,
		WindowUnfocused,
		WindowRefreshed,

	// Keyboard:

		KeyPressed,
		KeyRepeated,
		KeyReleased,
		CharPressed,

	// Mouse:

		MouseMoved,
		MouseEnteredWindow,
		MouseLeftWindow,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseScrolled,
		MousePathDropped,

	// Gamepad:

		GamepadConnected,
		GamepadDisconnected

	// UI:

		//

	// Gameplay:

		//
	};

//	struct FEventType
//	{
//	// Window:
//
//		static constexpr uint32 WindowClosed             = 0;
//		static constexpr uint32 WindowResized            = 1;
//		static constexpr uint32 WindowFrameBufferResized = 2;
//		static constexpr uint32 WindowContentScaled      = 3;
//		static constexpr uint32 WindowMoved              = 4;
//		static constexpr uint32 WindowIconified          = 5; // What is that???
//		static constexpr uint32 WindowMaximized          = 6;
//		static constexpr uint32 WindowFocused            = 7;
//		static constexpr uint32 WindowUnfocused          = 8;
//		static constexpr uint32 WindowRefreshed          = 9;
//
//	// Keyboard:
//
//		static constexpr uint32 KeyPressed     = 10;
//		static constexpr uint32 KeyRepeated    = 11;
//		static constexpr uint32 KeyReleased    = 12;
//		static constexpr uint32 KeyCharPressed = 13;
//
//	// Mouse:
//
//		static constexpr uint32 MouseMoved          = 14;
//		static constexpr uint32 MouseEntered        = 15;
//		static constexpr uint32 MouseLeft           = 16;
//		static constexpr uint32 MouseButtonPressed  = 17;
//		static constexpr uint32 MouseButtonReleased = 18;
//		static constexpr uint32 MouseScrolled       = 19;
//		static constexpr uint32 MouseDropped        = 20; // Mouse??? Paths of files and/or directories dropped on a window.
//
//	// Gamepad:
//
//		static constexpr uint32 GamepadConnected    = 21;
//		static constexpr uint32 GamepadDisconnected = 22;
//
//	// UI:
//
//		//
//
//	// Gameplay:
//
//		//
//	};
}