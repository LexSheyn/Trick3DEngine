#pragma once

#include "TComponent.h"
#include "../../Render/Primitives/Mesh/FMesh.h"

namespace t3d
{
	struct CModel : public TComponent<struct CModel>
	{
		FMesh* Mesh = nullptr;
	};
}