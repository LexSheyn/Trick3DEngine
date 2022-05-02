#pragma once

namespace t3d
{
	class IEventSender
	{
	protected:

	// SEventSystem Interface:

		static void T3D_CALL PushEvent    (FEvent&& Event);
	};
}