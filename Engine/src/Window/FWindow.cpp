#include "../PrecompiledHeaders/t3dpch.h"
#include "FWindow.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	FWindow::FWindow(int32 Width, int32 Height, const std::string& Title)
		: Width  (Width),
		  Height (Height),
		  Title  (Title),
		  Window (nullptr)
	{
		this->InitWindow();

		this->SetIcon("../Resources/T3D_logo_32.png");

	// Keyboard:

		FKeyboard::Initialize(Window);

		SEventSystem::Subscribe(EEventType::KeyPressed , &Keyboard);
		SEventSystem::Subscribe(EEventType::KeyReleased, &Keyboard);
		SEventSystem::Subscribe(EEventType::KeyRepeated, &Keyboard);
		SEventSystem::Subscribe(EEventType::CharPressed, &Keyboard);

	// Mouse:

		FMouse::Initialize(Window);

		SEventSystem::Subscribe(EEventType::MouseButtonPressed , &Mouse);
		SEventSystem::Subscribe(EEventType::MouseButtonReleased, &Mouse);
		SEventSystem::Subscribe(EEventType::MouseMoved         , &Mouse);
		SEventSystem::Subscribe(EEventType::MouseScrolled      , &Mouse);
		SEventSystem::Subscribe(EEventType::MouseEnteredWindow , &Mouse);
		SEventSystem::Subscribe(EEventType::MouseLeftWindow    , &Mouse);
		SEventSystem::Subscribe(EEventType::MousePathDropped   , &Mouse);
	}

	FWindow::~FWindow()
	{
		glfwDestroyWindow(Window);
		
		glfwTerminate();
	}


// Functions:

	void FWindow::Update()
	{
		glfwPollEvents();
	}

	bool8 FWindow::ShouldClose()
	{
		return glfwWindowShouldClose(Window);
	}

	void FWindow::CreateSurface(VkInstance Instance, VkSurfaceKHR* Surface)
	{
		if (glfwCreateWindowSurface(Instance, Window, nullptr, Surface) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create window surface!");
			throw;
		}
	}

	void FWindow::ResetResizedFlag()
	{
		FramebufferResized = false;
	}


// Accessors:

	const GLFWwindow* FWindow::GetGLFWwindow() const
	{
		return Window;
	}

	const bool8& FWindow::WasResized() const
	{
		return FramebufferResized;
	}

	const int32& FWindow::GetWidth() const
	{
		return Width;
	}

	const int32& FWindow::GetHeight() const
	{
		return Height;
	}

	VkExtent2D FWindow::GetExtent()
	{
		return { static_cast<uint32>(Width), static_cast<uint32>(Height) };
	}


// Modifiers:

	void FWindow::SetTitle(const std::string& Title)
	{
		glfwSetWindowTitle(Window, Title.c_str());
	}

	void FWindow::SetIcon(const std::string& FilePath)
	{
		FImagePNG Image = MImageManager::LoadImage(FilePath);

		TArray<GLFWimage, 1> Images{};

		Images[0].width  = Image.Width;
		Images[0].height = Image.Height;
		Images[0].pixels = Image.Pixels;

		glfwSetWindowIcon(Window, static_cast<int32>(Images.Size()), Images.Data());
	}


// Private Functions:

	void FWindow::InitWindow()
	{
	// GLFW initialization:

		glfwInit();

	// Window parameters and creation:

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE , GLFW_TRUE  );

		Window = glfwCreateWindow(Width, Height, Title.c_str(), nullptr, nullptr);

	// Get window user pointer to set event callbacks:

		glfwSetWindowUserPointer(Window, this);

	// Window events:

		glfwSetFramebufferSizeCallback(Window, FramebufferSizeCallback);

	// Keyboard events:

		glfwSetKeyCallback(Window, KeyCallback);
	
		glfwSetCharCallback(Window, CharCallback);
	
		glfwSetCharModsCallback(Window, CharModsCallback); // Deprecated, scheduled for removal in GLFW version 4.0.

	// Mouse events:

		glfwSetMouseButtonCallback(Window, MouseButtonCallback);
	
		glfwSetCursorPosCallback(Window, CursorPosCallback);
	
		glfwSetCursorEnterCallback(Window, CursorEnterCallback);
	
		glfwSetScrollCallback(Window, ScrollCallback);
	
		glfwSetDropCallback(Window, DropCallback);
	}


// Window Callbacks:

	void FWindow::FramebufferSizeCallback(GLFWwindow* Window, int32 Width, int32 Height)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));

		WindowPtr->FramebufferResized = true;

		WindowPtr->Width  = Width;
		WindowPtr->Height = Height;

		SEventSystem::PushEvent(FEvent(EEventType::WindowResized, FFrameBufferSizeData(Width, Height)));
	}


// Keyboard Callbacks:

	void FWindow::KeyCallback(GLFWwindow* Window, int32 Key, int32 ScanCode, int32 Action, int32 Mods)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));

		if (Action == GLFW_PRESS)
		{
			SEventSystem::PushEvent(FEvent(EEventType::KeyPressed, FKeyData{ Key, ScanCode, Action, Mods }));
		}
		else if (Action == GLFW_REPEAT)
		{
			//
		}
		else if (Action == GLFW_RELEASE)
		{
			SEventSystem::PushEvent(FEvent(EEventType::KeyReleased, FKeyData{ Key, ScanCode, Action, Mods }));
		}
	}

	void FWindow::CharCallback(GLFWwindow* Window, uint32 Codepoint)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));
	}

	void FWindow::CharModsCallback(GLFWwindow* Window, uint32 Codepoint, int32 Mods)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));
	}


// Mouse Callbacks:

	void FWindow::MouseButtonCallback(GLFWwindow* Window, int32 Button, int32 Action, int32 Mods)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));

		if (Action == GLFW_PRESS)
		{

		}
		else if (Action == GLFW_RELEASE)
		{

		}
	}

	void FWindow::CursorPosCallback(GLFWwindow* Window, float64 X, float64 Y)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));
	}

	void FWindow::CursorEnterCallback(GLFWwindow* Window, int32 Entered)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));
	}

	void FWindow::ScrollCallback(GLFWwindow* Window, float64 OffsetX, float64 OffsetY)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));
	}

	void FWindow::DropCallback(GLFWwindow* Window, int32 PathCount, const char8* Paths[])
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));
	}

}

#pragma warning( pop ) // Vulkan SDK - End