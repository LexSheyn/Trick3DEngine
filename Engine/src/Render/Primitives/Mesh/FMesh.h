#pragma once

#include "../../Core/FDevice.h"
#include "../../Core/FDeviceBuffer.h"
#include "FMeshData.h"

namespace t3d
{
	class FMesh
	{
	public:

	// Constructors and Destructor:

		using Data = FMeshData;

		FMesh(FDevice& Device, const FMesh::Data& MeshData);

		FMesh(FDevice& Device, const std::string& FilePath);

		~FMesh();

		T3D_NO_COPY(FMesh);
		T3D_NO_MOVE(FMesh);

	// Functions:

		void Bind(VkCommandBuffer CommandBuffer);

		void Draw(VkCommandBuffer CommandBuffer);

	private:

	// Private Functions:

		void CreateVertexBuffer(const std::vector<FVertex>& Vertices);

		void CreateIndexBuffer(const std::vector<uint32>& Indices);

	// Variables:

		FDevice& Device;

		FDeviceBuffer* VertexBuffer;
		uint32 VertexCount;

		FDeviceBuffer* IndexBuffer;
		uint32 IndexCount;
	};
}