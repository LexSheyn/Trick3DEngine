#pragma once

#include "TComponent.h"
#include "../../Render/Core/FCamera.h"

namespace t3d
{
	struct CCamera : public TComponent<struct CCamera>
	{
		FCamera* Camera;
	};
}