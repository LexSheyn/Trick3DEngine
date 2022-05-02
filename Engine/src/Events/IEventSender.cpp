#include "../PCH/t3dpch.h"
#include "IEventSender.h"

namespace t3d
{
// SEventSystem Interface:

	void IEventSender::PushEvent(FEvent&& Event)
	{
		SEventSystem::PushEvent(std::move(Event));
	}


}