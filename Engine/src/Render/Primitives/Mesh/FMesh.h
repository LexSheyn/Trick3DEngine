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

		void T3D_CALL CreateVertexBuffer    (FDevice& Device, const std::vector<FVertex>& Vertices);
		void T3D_CALL CreateIndexBuffer     (FDevice& Device, const std::vector<T3D_Index>& Indices);

		void T3D_CALL Bind    (VkCommandBuffer CommandBuffer);
		void T3D_CALL Draw    (VkCommandBuffer CommandBuffer);

	private:

	// Variables:

		FDeviceBuffer* VertexBuffer;
		uint32         VertexCount;

		FDeviceBuffer* IndexBuffer;
		uint32         IndexCount;
	};
}