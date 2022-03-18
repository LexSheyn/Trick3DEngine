#pragma once

#include "../../Core/FDeviceBuffer.h"
#include "FMeshData.h"
#include "FMeshUniform.h"
#include "FMeshPushConstant.h"

namespace t3d
{
	class FMesh
	{
	public:

	// Constructors and Destructor:

		 FMesh ();
		~FMesh ();

		T3D_NO_COPY(FMesh);
		T3D_NO_MOVE(FMesh);

	// Functions:

		void CreateVertexBuffer    (FDevice& Device, const std::vector<FVertex>& Vertices);
		void CreateIndexBuffer     (FDevice& Device, const std::vector<T3D_Index>& Indices);

		void Bind    (VkCommandBuffer CommandBuffer);
		void Draw    (VkCommandBuffer CommandBuffer);

	private:

	// Variables:

		FDeviceBuffer* VertexBuffer;
		uint32         VertexCount;

		FDeviceBuffer* IndexBuffer;
		uint32         IndexCount;
	};
}