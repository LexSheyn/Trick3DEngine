#pragma once

#include "FVertex.h"

namespace t3d
{
	struct FMeshData
	{
		std::vector<FVertex>    Vertices;
		std::vector<T3D_Index>  Indices;
	};
}