#pragma once

namespace t3d
{
	template<typename T>
	struct TEventCallbackRecord
	{
		void* Instance;
		T     Callback;
	};
}