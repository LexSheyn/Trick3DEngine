#pragma once

#include "TComponent.h"

namespace t3d
{
	struct CPointLight : public TComponent<struct CPointLight>
	{
		FVec3   Position;
		FVec4   Color; // w used for intensity.
		float32 Radius;
	};
}