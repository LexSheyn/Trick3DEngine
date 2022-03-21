#pragma once

#include "TComponent.h"

namespace t3d
{
	struct CDirectionalLight : public TComponent<struct CDirectionalLight>
	{
		FVec3 Direction;
		FVec4 Color; // w used for intensity.		
	};
}