#pragma once

#include "FVertex.h"

namespace t3d
{
	class FMeshData
	{
	public:

	// Constructors and Destructor:

		FMeshData();

		FMeshData(const std::vector<FVertex>& Vertices, const std::vector<uint32>& Indices);

		~FMeshData();

	// Functions:

		void LoadOBJ(const std::string& FilePath);

	// Public Variables:

		std::vector<FVertex> Vertices;

		std::vector<uint32>  Indices;
	};
}