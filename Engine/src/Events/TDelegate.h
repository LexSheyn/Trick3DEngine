#pragma once

namespace t3d
{
	template<typename T>
	struct TDelegate
	{
		using Callback_Type = bool8 (*) (const T&);

		Callback_Type Callback;
	};
}