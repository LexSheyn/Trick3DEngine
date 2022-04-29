#pragma once

namespace t3d
{
	template<typename T>
	struct TDelegate
	{
		void (*Callback) (const T&);
	};
}