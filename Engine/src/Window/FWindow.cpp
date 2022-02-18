#include "../PrecompiledHeaders/t3dpch.h"
#include "FWindow.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	FWindow::FWindow(int32 Width, int32 Height, const std::string& Title)
		: Width(Width),
		  Height(Height),
		  Title(Title),
		  Window(nullptr)
	{
		this->InitWindow();

		this->SetIcon("../Resources/T3D_logo_32.png");

	// Keyboard:

		FKeyboard::Initialize(Window);

		FEventSystem::Subscribe(EEventType::KeyPressed , &Keyboard);
		FEventSystem::Subscribe(EEventType::KeyReleased, &Keyboard);
		FEventSystem::Subscribe(EEventType::KeyRepeated, &Keyboard);
		FEventSystem::Subscribe(EEventType::CharPressed, &Keyboard);

	// Mouse:

		FMouse::Initialize(Window);

		FEventSystem::Subscribe(EEventType::MouseButtonPressed , &Mouse);
		FEventSystem::Subscribe(EEventType::MouseButtonReleased, &Mouse);
		FEventSystem::Subscribe(EEventType::MouseMoved         , &Mouse);
		FEventSystem::Subscribe(EEventType::MouseScrolled      , &Mouse);
		FEventSystem::Subscribe(EEventType::MouseEnteredWindow , &Mouse);
		FEventSystem::Subscribe(EEventType::MouseLeftWindow    , &Mouse);
		FEventSystem::Subscribe(EEventType::MousePathDropped   , &Mouse);
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


// Modifiers:

	void FWindow::SetTitle(const std::string& Title)
	{
		glfwSetWindowTitle(Window, Title.c_str());
	}

	void FWindow::SetIcon(const std::string& FilePath)
	{
		FImagePNG Image = FImageLoader::LoadFromFile(FilePath);

		TArray<GLFWimage, 1> Images{};

		Images[0].width  = Image.Width;
		Images[0].height = Image.Height;
		Images[0].pixels = Image.Pixels;

		glfwSetWindowIcon(Window, static_cast<int32>(Images.Size()), Images.Data());
	}

//	void FWindow::SetFunctionCallback(const std::function<void(Event&)>& Function)
//	{
//		FunctionCallback = Function;
//	}

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

	//	this->SetFunctionCallback([](Event& E)
	//	{
	//		std::cout << E.Format();
	//	});
	}


// Window Callbacks:

	void FWindow::FramebufferSizeCallback(GLFWwindow* Window, int32 Width, int32 Height)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));

		WindowPtr->FramebufferResized = true;

		WindowPtr->Width  = Width;
		WindowPtr->Height = Height;
	}


// Keyboard Callbacks:

	void FWindow::KeyCallback(GLFWwindow* Window, int32 Key, int32 ScanCode, int32 Action, int32 Mods)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));

		if (Action == GLFW_PRESS)
		{
		//	Keyboard.OnKeyPress(Key);

			FEventSystem::PushEvent(FEvent(EEventType::KeyPressed, FKeyData{ Key, ScanCode, Action, Mods }));

		//	std::cout << __FUNCTION__ << ": Key: " << Key << " :: " << ScanCode << " Press " << ":: " << Mods << std::endl;
		}
		else if (Action == GLFW_REPEAT)
		{
		//	Keyboard.OnKeyRepeat(Key);

		//	std::cout << __FUNCTION__ << ": Key: " << Key << " :: " << ScanCode << " Repeat " << ":: " << Mods << std::endl;
		}
		else if (Action == GLFW_RELEASE)
		{
		//	Keyboard.OnKeyRelease(Key);

			FEventSystem::PushEvent(FEvent(EEventType::KeyReleased, FKeyData{ Key, ScanCode, Action, Mods }));

		//	std::cout << __FUNCTION__ << ": Key: " << Key << " :: " << ScanCode << " Release " << ":: " << Mods << std::endl;
		}
	}

	void FWindow::CharCallback(GLFWwindow* Window, uint32 Codepoint)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));

	//	std::cout << __FUNCTION__ << ": Char: " << static_cast<char8>(Codepoint) << std::endl;
	}

	void FWindow::CharModsCallback(GLFWwindow* Window, uint32 Codepoint, int32 Mods)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));

	//	std::cout << __FUNCTION__ << ": Char: " << static_cast<char8>(Codepoint) << " Mods: " << Mods << std::endl;
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

	//	std::cout << __FUNCTION__ << ": Mouse Button: " << Button << " :: " << Action << " :: " << Mods << std::endl;
	}

	void FWindow::CursorPosCallback(GLFWwindow* Window, float64 X, float64 Y)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));

	//	std::cout << __FUNCTION__ << ": Mouse Position: " << "x: " << X << " / " << "y: " << Y << std::endl;
	}

	void FWindow::CursorEnterCallback(GLFWwindow* Window, int32 Entered)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));

	//	std::cout << __FUNCTION__ << ": Mouse Entered: " << Entered << std::endl;
	}

	void FWindow::ScrollCallback(GLFWwindow* Window, float64 OffsetX, float64 OffsetY)
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));

	//	std::cout << __FUNCTION__ << ": Mouse Scroll: " << OffsetX << " / " << OffsetY << std::endl;
	}

	void FWindow::DropCallback(GLFWwindow* Window, int32 PathCount, const char8* Paths[])
	{
		FWindow* WindowPtr = reinterpret_cast<FWindow*>(glfwGetWindowUserPointer(Window));

	//	std::cout << __FUNCTION__ << ": Drop: " << PathCount << " :: " << Paths;
	}

}

#pragma warning( pop ) // Vulkan SDK - End