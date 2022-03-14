#pragma once

#include "../IInputDevice.h"
#include "FKeyEvent.h"
#include "FCharEvent.h"
#include "FKeyState.h"
#include "../../Events/IEventListener.h"

namespace t3d
{
	class FKeyboard : public IInputDevice, public IEventListener
	{
	public:

	// IEventListener interface:

		void OnEvent(const FEvent* const) override;

	// Functions:

		static bool8 IsKeyPressed(int32 Key);

		static bool8 IsKeyReleased(int32 Key);

		void ProcessKeys();

	private:

	// Private Constructors and Destructor:

		FKeyboard();

		FKeyboard(const FKeyboard&) = delete;

		~FKeyboard();

	// Private Operators:

		FKeyboard& operator=(const FKeyboard&) = delete;

	// Private Functions:

		static void Initialize(GLFWwindow* Window);

		void PushKeyEvent(const FKeyEvent& KeyEvent);

		void OnKeyPress(int32 Key, int32 Action);

		void OnKeyRepeat(int32 Key, int32 Action);

		void OnKeyRelease(int32 Key, int32 Action);

		/// <summary>
		/// Characters format is native endian UTF-32.
		/// </summary>
		/// <param name="Character">: Character representer as uint32 number. </param>
		static void OnChar(uint32 Character); // ??? GLFW ???

		template<typename T>
		void TrimBuffer(std::deque<T>& Buffer)
		{
			while (Buffer.size() > BufferSize)
			{
				Buffer.pop_back();
			}
		}

	// Variables:

		static GLFWwindow* Window;

		bool8 IsAutorepeatEnabled;

		static constexpr uint32 NumKeys = 256;

		static constexpr uint64 BufferSize = 16;

		std::deque<FKeyEvent> KeyBuffer;
	
		std::deque<char8> CharBuffer;

	// Friends:

		friend class FWindow;
	};
}