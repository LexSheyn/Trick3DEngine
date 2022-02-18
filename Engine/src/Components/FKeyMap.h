#pragma once

namespace t3d
{
	class FKeyMap
	{
	public:

        int32 MoveLeft     = GLFW_KEY_A;
        int32 MoveRight    = GLFW_KEY_D;
        int32 MoveForward  = GLFW_KEY_W;
        int32 MoveBackward = GLFW_KEY_S;
        int32 MoveUp       = GLFW_KEY_E;
        int32 MoveDown     = GLFW_KEY_Q;
        int32 LookLeft     = GLFW_KEY_LEFT;
        int32 LookRight    = GLFW_KEY_RIGHT;
        int32 LookUp       = GLFW_KEY_UP;
        int32 LookDown     = GLFW_KEY_DOWN;
	};
}