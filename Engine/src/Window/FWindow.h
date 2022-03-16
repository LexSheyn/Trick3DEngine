#pragma once

#include "../Input/Keyboard/FKeyboard.h"
#include "../Input/Mouse/FMouse.h"
#include "../Input/Gamepad/FGamepad.h"
#include "../ResourceManagers/Image/MImageManager.h"

namespace t3d
{
	class FWindow
	{
	public:

	// Constructors and Destructor:

		 FWindow (int32 Width, int32 Height, const std::string& Title);
		~FWindow ();

		T3D_NO_COPY(FWindow);
		T3D_NO_MOVE(FWindow);

	// Functions:

		void  T3D_CALL Update              ();
		bool8 T3D_CALL ShouldClose         ();
		void  T3D_CALL CreateSurface       (VkInstance Instance, VkSurfaceKHR* Surface);
		void  T3D_CALL ResetResizedFlag    ();

	// Accessors:

		const GLFWwindow* T3D_CALL GetGLFWwindow    () const;
		const bool8&      T3D_CALL WasResized       () const;
		const int32&      T3D_CALL GetWidth         () const;
		const int32&      T3D_CALL GetHeight        () const;

		VkExtent2D T3D_CALL GetExtent();

	// Modifiers:

		void T3D_CALL SetTitle    (const std::string& Title);
		void T3D_CALL SetIcon     (const std::string& FilePath);

	private:

	// Private Functions:

		void T3D_CALL InitWindow();

	// Window Callbacks:

		static void T3D_CALL FramebufferSizeCallback(GLFWwindow* Window, int32 Width, int32 Height);

	// Keyboard Callbacks:

		static void T3D_CALL KeyCallback         (GLFWwindow* Window, int32 Key, int32 ScanCode, int32 Action, int32 Mods);
		static void T3D_CALL CharCallback        (GLFWwindow* Window, uint32 Codepoint);		
		static void T3D_CALL CharModsCallback    (GLFWwindow* Window, uint32 Codepoint, int32 Mods); // Deprecated, scheduled for removal in GLFW version 4.0.

	// Mouse Callbacks:

		static void T3D_CALL MouseButtonCallback    (GLFWwindow* Window, int32 Button, int32 Action, int32 Mods);
		static void T3D_CALL CursorPosCallback      (GLFWwindow* Window, float64 X, float64 Y);
		static void T3D_CALL CursorEnterCallback    (GLFWwindow* Window, int32 Entered);
		static void T3D_CALL ScrollCallback         (GLFWwindow* Window, float64 OffsetX, float64 OffsetY);
		static void T3D_CALL DropCallback           (GLFWwindow* Window, int32 PathCount, const char8* Paths[]);

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
	};
}