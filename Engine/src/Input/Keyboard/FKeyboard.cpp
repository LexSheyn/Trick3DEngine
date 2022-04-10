#include "../../PCH/t3dpch.h"
#include "FKeyboard.h"

namespace t3d
{
// IEventListener interface:

	void FKeyboard::OnEvent(const FEvent* const)
	{
		//
	}

// Functions:

	bool8 FKeyboard::IsKeyPressed(int32 Key)
	{
		return static_cast<bool8>(glfwGetKey(Window, Key) == FKeyState::Pressed);
	}

	bool8 FKeyboard::IsKeyReleased(int32 Key)
	{
		return static_cast<bool8>(glfwGetKey(Window, Key) == FKeyState::Released);
	}

	void FKeyboard::ProcessKeys()
	{
	}


// Private Constructors and Destructor:

	FKeyboard::FKeyboard()
		: IsAutorepeatEnabled(true)
	{
	}

	FKeyboard::~FKeyboard()
	{
		KeyBuffer.clear();
		CharBuffer.clear();
	}


// Private Functions:

	void FKeyboard::Initialize(GLFWwindow* Window)
	{
		FKeyboard::Window = Window;
	}

	void FKeyboard::PushKeyEvent(const FKeyEvent& KeyEvent)
	{
		KeyBuffer.push_back(KeyEvent);

		TrimBuffer(KeyBuffer);
	}

	void FKeyboard::OnKeyPress(int32 Key, int32 Action)
	{
	//	KeyBuffer.push_back(FKeyEvent(Key, FKeyEvent::FType::Press));
	//
	//	TrimBuffer(KeyBuffer);
	}

	void FKeyboard::OnKeyRepeat(int32 Key, int32 Action)
	{
	//	KeyBuffer.push_back(FKeyEvent(Key, FKeyEvent::FType::Repeat));
	//
	//	TrimBuffer(KeyBuffer);
	}

	void FKeyboard::OnKeyRelease(int32 Key, int32 Action)
	{
	//	KeyBuffer.push_back(FKeyEvent(Key, FKeyEvent::FType::Release));
	//
	//	TrimBuffer(KeyBuffer);
	}

	void FKeyboard::OnChar(uint32 Character)
	{
	//	CharBuffer.push_back(static_cast<char8>(Character));
	//
	//	TrimBuffer(CharBuffer);
	}


// Static Variables:

	GLFWwindow* FKeyboard::Window = nullptr;

}

