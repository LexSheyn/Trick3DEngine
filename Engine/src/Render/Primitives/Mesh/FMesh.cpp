#include "../../../PCH/t3dpch.h"
#include "FMesh.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	FMesh::FMesh()
		: VertexBuffer(nullptr), 
		  VertexCount(),
		  IndexBuffer(nullptr),
		  IndexCount()
	{

		SEvent::Trace.Invoke({ FTimeStamp(), T3D_FUNCTION, "Created." });
	}

	FMesh::~FMesh()
	{
		delete IndexBuffer;

		delete VertexBuffer;

		SEvent::Trace.Invoke({ FTimeStamp(), T3D_FUNCTION, "Deleted." });
	}


// Functions:

	void FMesh::CreateVertexBuffer(FDevice& Device, const std::vector<FVertex>& Vertices)
	{
		VertexCount = static_cast<uint32>(Vertices.size());

		SEvent::Trace.Invoke({ FTimeStamp(), T3D_FUNCTION, std::string("Vertex count: " + std::to_string(VertexCount)).c_str() });

	#if _DEBUG
		if (VertexCount < 3u)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Vertex count must be at least 3!" });
			throw;
		}
	#endif

		VkDeviceSize BufferSize = sizeof(Vertices[0]) * VertexCount;

		uint32 VertexSize = sizeof(Vertices[0]);

		FDeviceBuffer StagingBuffer(Device, VertexSize, VertexCount, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		StagingBuffer.Map();
		StagingBuffer.WriteToBuffer(reinterpret_cast<void*>(const_cast<FVertex*>(Vertices.data())));
		StagingBuffer.Unmap();

		VertexBuffer = new FDeviceBuffer(Device, VertexSize, VertexCount, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		Device.CopyBuffer(StagingBuffer.GetBuffer(), VertexBuffer->GetBuffer(), BufferSize);
	}

	void FMesh::CreateIndexBuffer(FDevice& Device, const std::vector<T3D_Index>& Indices)
	{
		IndexCount = static_cast<uint32>(Indices.size());

		SEvent::Trace.Invoke({ FTimeStamp(), T3D_FUNCTION, std::string("Index count: " + std::to_string(IndexCount)).c_str() });

	#if _DEBUG
		if (IndexCount == 0u)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Non indexed mesh is not supported!" });
			throw;
		}
	#endif

		VkDeviceSize BufferSize = sizeof(Indices[0]) * IndexCount;

		uint32 IndexSize = sizeof(Indices[0]);

		FDeviceBuffer StagingBuffer(Device, IndexSize, IndexCount, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		StagingBuffer.Map();
		StagingBuffer.WriteToBuffer(reinterpret_cast<void*>(const_cast<T3D_Index*>(Indices.data())));
		StagingBuffer.Unmap();

		IndexBuffer = new FDeviceBuffer(Device, IndexSize, IndexCount, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		Device.CopyBuffer(StagingBuffer.GetBuffer(), IndexBuffer->GetBuffer(), BufferSize);
	}

	void FMesh::Bind(VkCommandBuffer CommandBuffer)
	{
		VkBuffer     Buffers[] = { VertexBuffer->GetBuffer() };
		VkDeviceSize Offsets[] = { 0 };

		vkCmdBindVertexBuffers(CommandBuffer, 0, 1, Buffers, Offsets);

		vkCmdBindIndexBuffer(CommandBuffer, IndexBuffer->GetBuffer(), 0, VK_INDEX_TYPE_UINT32);
	}

	void FMesh::Draw(VkCommandBuffer CommandBuffer)
	{
		vkCmdDrawIndexed(CommandBuffer, IndexCount, 1, 0, 0, 0);
	}

}

#pragma warning( pop ) // Vulkan SDK - End