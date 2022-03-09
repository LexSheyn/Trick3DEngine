#pragma once

#include "../Events/SEventSystem.h"
#include "../Input/Keyboard/FKeyboard.h"
#include "../Input/Mouse/FMouse.h"
#include "../Input/Gamepad/FGamepad.h"

namespace t3d
{
	class FWindow
	{
	public:

	// Constructors and Destructor:

		FWindow(int32 Width, int32 Height, const std::string& Title);

		~FWindow();

		T3D_NO_COPY(FWindow);
		T3D_NO_MOVE(FWindow);

	// Functions:

		void Update();

		bool8 ShouldClose();

		void CreateSurface(VkInstance Instance, VkSurfaceKHR* Surface);

		T3D_INLINE void ResetResizedFlag() { FramebufferResized = false; }

	// Accessors:

		T3D_INLINE const GLFWwindow* GetGLFWwindow() const { return Window; }

		T3D_INLINE       VkExtent2D  GetExtent()           { return { static_cast<uint32>(Width), static_cast<uint32>(Height) }; }

		T3D_INLINE const bool8&      WasResized()    const { return FramebufferResized; }

		T3D_INLINE const int32&      GetWidth()      const { return Width; }

		T3D_INLINE const int32&      GetHeight()     const { return Height; }

	// Modifiers:

		void SetTitle(const std::string& Title);

		void SetIcon(const std::string& FilePath);

	private:

	// Private Functions:

		void InitWindow();

	// Window Callbacks:

		static void FramebufferSizeCallback(GLFWwindow* Window, int32 Width, int32 Height);

	// Keyboard Callbacks:

		static void KeyCallback(GLFWwindow* Window, int32 Key, int32 ScanCode, int32 Action, int32 Mods);

		static void CharCallback(GLFWwindow* Window, uint32 Codepoint);

		// Deprecated, scheduled for removal in GLFW version 4.0.
		static void CharModsCallback(GLFWwindow* Window, uint32 Codepoint, int32 Mods);

	// Mouse Callbacks:

		static void MouseButtonCallback(GLFWwindow* Window, int32 Button, int32 Action, int32 Mods);

		static void CursorPosCallback(GLFWwindow* Window, float64 X, float64 Y);

		static void CursorEnterCallback(GLFWwindow* Window, int32 Entered);

		static void ScrollCallback(GLFWwindow* Window, float64 OffsetX, float64 OffsetY);

		static void DropCallback(GLFWwindow* Window, int32 PathCount, const char8* Paths[]);

	// Variables:

		int32 Width;
		int32 Height;
		bool8 FramebufferResized;

		std::string Title;

		GLFWwindow* Window;

	// Input Devices:

		FKeyboard Keyboard;
		FMouse    Mouse;
		FGamepad  Gamepad;

	//	std::function<void(Event&)> FunctionCallback;
	};
}