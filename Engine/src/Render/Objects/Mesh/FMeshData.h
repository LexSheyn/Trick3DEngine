#pragma once

#include "FVertex.h"

namespace t3d
{
	class FMeshData
	{
	public:

	// Functions:

		void LoadOBJ(const std::string& FilePath);

	// Public Variables:

		std::vector<FVertex> Vertices;

		std::vector<uint32>  Indices;
	};
}