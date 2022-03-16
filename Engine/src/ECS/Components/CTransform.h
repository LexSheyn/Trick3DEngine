#pragma once

#include "TComponent.h"

namespace t3d
{
	struct CTransform : public TComponent<struct CTransform>
	{
		FVec3 Translation { 0.0f };
		FVec3 Rotation    { 0.0f };
		FVec3 Scale       { 1.0f };
	};
}