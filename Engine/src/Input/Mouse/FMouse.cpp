#include "../../PrecompiledHeaders/t3dpch.h"
#include "FMouse.h"

namespace t3d
{
// IEventListener interface:

    void FMouse::OnEvent(const FEvent* const)
    {
    }


// Functions:

    bool8 FMouse::IsButtonPressed(int32 Button)
    {
        return static_cast<bool8>(glfwGetMouseButton(Window, Button) == FMouseButtonState::Pressed);
    }

    bool8 FMouse::IsButtonReleased(int32 Button)
    {
        return static_cast<bool8>(glfwGetMouseButton(Window, Button) == FMouseButtonState::Released);
    }

    void FMouse::ProcessButtons()
    {
    }


// Accessors:

    float32 FMouse::GetX()
    {
        float64 X;
        float64 Y;

        glfwGetCursorPos(Window, &X, &Y);

        return static_cast<float32>(X);
    }

    float32 FMouse::GetY()
    {
        float64 X;
        float64 Y;

        glfwGetCursorPos(Window, &X, &Y);

        return static_cast<float32>(Y);
    }


// Private Constructors and Destructor:

    FMouse::FMouse()
    {
    }

    FMouse::~FMouse()
    {
    }


// Private Functions:

    void FMouse::Initialize(GLFWwindow* Window)
    {
        FMouse::Window = Window;
    }


// Static Variables:

    GLFWwindow* FMouse::Window = nullptr;

}