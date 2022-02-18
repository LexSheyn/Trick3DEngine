#include "../../../PrecompiledHeaders/t3dpch.h"
#include "FMesh.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	FMesh::FMesh(FDevice& Device, const FMesh::Data& MeshData)
		: Device(Device),
		  HasIndexBuffer(false)
	{
		this->CreateVertexBuffer(MeshData.Vertices);

		this->CreateIndexBuffer(MeshData.Indices);

		LOG_TRACE("Created.");
	}

	FMesh::~FMesh()
	{
	}


// Functions:

	std::unique_ptr<FMesh> FMesh::CreateFromFile(FDevice& Device, const std::string& FilePath)
	{
		FMesh::Data MeshData;

		MeshData.LoadOBJ(FilePath);

		return std::make_unique<FMesh>(Device, MeshData);
	}

	void FMesh::Bind(VkCommandBuffer CommandBuffer)
	{
		VkBuffer Buffers[] = { VertexBuffer->GetBuffer() };

		VkDeviceSize Offsets[] = { 0 };

		vkCmdBindVertexBuffers(CommandBuffer, 0, 1, Buffers, Offsets);

		if (HasIndexBuffer)
		{
			vkCmdBindIndexBuffer(CommandBuffer, IndexBuffer->GetBuffer(), 0, VK_INDEX_TYPE_UINT32);
		}
	}

	void FMesh::Draw(VkCommandBuffer CommandBuffer)
	{
		if (HasIndexBuffer)
		{
			vkCmdDrawIndexed(CommandBuffer, IndexCount, 1, 0, 0, 0);
		}
		else
		{
			vkCmdDraw(CommandBuffer, VertexCount, 1, 0, 0);
		}
	}


// Private Functions:

	void FMesh::CreateVertexBuffer(const std::vector<FVertex>& Vertices)
	{
		VertexCount = static_cast<uint32>(Vertices.size());

		LOG_TRACE("Vertex count: " + std::to_string(VertexCount));

		if (VertexCount < 3u)
		{
			LOG_ERROR("Vertex count must be at least 3!");
			throw;
		}

		VkDeviceSize BufferSize = sizeof(Vertices[0]) * VertexCount;

		uint32 VertexSize = sizeof(Vertices[0]);

		FDeviceBuffer StagingBuffer(Device, VertexSize, VertexCount, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		StagingBuffer.Map();
		StagingBuffer.WriteToBuffer(reinterpret_cast<void*>(const_cast<FVertex*>(Vertices.data())));
		StagingBuffer.Unmap();

		VertexBuffer = std::make_unique<FDeviceBuffer>(Device, VertexSize, VertexCount, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		Device.CopyBuffer(StagingBuffer.GetBuffer(), VertexBuffer->GetBuffer(), BufferSize);
	}

	void FMesh::CreateIndexBuffer(const std::vector<uint32>& Indices)
	{
		IndexCount = static_cast<uint32>(Indices.size());

		HasIndexBuffer = IndexCount > 0u;

		if (!HasIndexBuffer)
		{
			return;
		}

		LOG_TRACE("Index count: " + std::to_string(IndexCount));

		VkDeviceSize BufferSize = sizeof(Indices[0]) * IndexCount;

		uint32 IndexSize = sizeof(Indices[0]);

		FDeviceBuffer StagingBuffer(Device, IndexSize, IndexCount, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		StagingBuffer.Map();
		StagingBuffer.WriteToBuffer(reinterpret_cast<void*>(const_cast<uint32*>(Indices.data())));
		StagingBuffer.Unmap();

		IndexBuffer = std::make_unique<FDeviceBuffer>(Device, IndexSize, IndexCount, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		Device.CopyBuffer(StagingBuffer.GetBuffer(), IndexBuffer->GetBuffer(), BufferSize);
	}

}

#pragma warning( pop ) // Vulkan SDK - End