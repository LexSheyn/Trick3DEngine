#pragma once

#include "../IInputDevice.h"
#include "FMouseButton.h"
//#include "FMouseEvent.h"
#include "FMouseButtonState.h"
#include "../../Events/IEventListener.h"

namespace t3d
{
	class FMouse : IInputDevice, public IEventListener
	{
	public:

	// IEventListener interface:
		
		void OnEvent(const FEvent* const) override;

	// Functions:

		static bool8 IsButtonPressed(int32 Button);

		static bool8 IsButtonReleased(int32 Button);

		void ProcessButtons();

	// Accessors:

		static float32 GetX();

		static float32 GetY();

	private:

	// Private Constructors and Destructor:

		FMouse();

		FMouse(const FMouse&) = delete;

		~FMouse();

	// Private Operators:

		FMouse& operator=(const FMouse&) = delete;

	// Private Functions:

		static void Initialize(GLFWwindow* Window);

		//

		//

		//

		//

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

	//	bool8 IsAutorepeatEnabled;

		static constexpr uint32 NumButtons = 6;

		static constexpr uint64 BufferSize = 16;

	//	std::deque<FMouseEvent> ButtonBuffer;

		//

	// Friends:

		friend class FWindow;
	};
}