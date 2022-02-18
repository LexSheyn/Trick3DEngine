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

		FMesh(const FMesh&) = delete;

		~FMesh();

	// Operators:

		FMesh& operator=(const FMesh&) = delete;

	// Functions:

		static std::unique_ptr<FMesh> CreateFromFile(FDevice& Device, const std::string& FilePath);

		void Bind(VkCommandBuffer CommandBuffer);

		void Draw(VkCommandBuffer CommandBuffer);

	private:

	// Private Functions:

		void CreateVertexBuffer(const std::vector<FVertex>& Vertices);

		void CreateIndexBuffer(const std::vector<uint32>& Indices);

	// Variables:

		FDevice& Device;

		std::unique_ptr<FDeviceBuffer> VertexBuffer;
		uint32 VertexCount;

		bool8 HasIndexBuffer;
		std::unique_ptr<FDeviceBuffer> IndexBuffer;
		uint32 IndexCount;
	};
}