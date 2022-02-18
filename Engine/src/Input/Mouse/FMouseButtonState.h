#pragma once

struct FMouseButtonState
{
	static constexpr int32 Released = 0;
	static constexpr int32 Pressed  = 1;
	static constexpr int32 Repeated = 2;
};