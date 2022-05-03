#pragma once

namespace t3d
{	
	enum class EEventType
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
		CharWithModsPressed,

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
		GamepadDisconnected,

	// Application:

		//

	// UI:

		//

	// Gameplay:

		//
	};
}