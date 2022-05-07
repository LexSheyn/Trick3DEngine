#include "../../PCH/t3dpch.h"
#include "MModelManager.h"

#include "../../Render/Primitives/Mesh/FMesh.h"
#include "../../ThirdParty/tiny_obj_loader.h"

namespace t3d
{
// Functions:

	FMesh* MModelManager::LoadModel(const std::string& FilePath)
	{
		FMeshData MeshData;

		tinyobj::attrib_t Attributes;

		std::vector<tinyobj::shape_t> Shapes;
		std::vector<tinyobj::material_t> Materials;

		std::string WarningMessage;
		std::string ErrorMessage;

		if (!tinyobj::LoadObj(&Attributes, &Shapes, &Materials, &WarningMessage, &ErrorMessage, FilePath.c_str()))
		{
			SEvent::Warning.Invoke({ FTimeStamp(), T3D_FUNCTION, WarningMessage.c_str() });
			SEvent::Error  .Invoke({ FTimeStamp(), T3D_FUNCTION, ErrorMessage.c_str() });
			throw;
		}

		std::unordered_map<FVertex, T3D_Index> UniqueVertices;

		for (const auto& Shape : Shapes)
		{
			for (const auto& Index : Shape.mesh.indices)
			{
				FVertex Vertex{};

				if (Index.vertex_index >= 0)
				{
					Vertex.Position =
					{
						Attributes.vertices[3 * Index.vertex_index + 0],
						Attributes.vertices[3 * Index.vertex_index + 1],
						Attributes.vertices[3 * Index.vertex_index + 2]
					};

					Vertex.Color = FVec3(0.5f);
				//	{
				//		Attributes.colors[3 * Index.vertex_index + 0],
				//		Attributes.colors[3 * Index.vertex_index + 1],
				//		Attributes.colors[3 * Index.vertex_index + 2]
				//	};
				}

				if (Index.normal_index >= 0)
				{
					Vertex.Normal =
					{
						Attributes.normals[3 * Index.normal_index + 0],
						Attributes.normals[3 * Index.normal_index + 1],
						Attributes.normals[3 * Index.normal_index + 2]
					};
				}

				if (Index.texcoord_index >= 0)
				{
					Vertex.TexCoord =
					{
						Attributes.texcoords[2 * Index.texcoord_index + 0],
						Attributes.texcoords[2 * Index.texcoord_index + 1]
					};
				}

				if (UniqueVertices.count(Vertex) == 0u)
				{
					UniqueVertices[Vertex] = static_cast<uint32>(MeshData.Vertices.size());

					MeshData.Vertices.push_back(Vertex);
				}

				MeshData.Indices.push_back(UniqueVertices[Vertex]);
			}
		}

		FMesh* Mesh = new FMesh(); // Specify where in the future!

		Mesh->CreateVertexBuffer(*Device, MeshData.Vertices);
		Mesh->CreateIndexBuffer (*Device, MeshData.Indices);

		return Mesh;
	}


// Modifiers:

	void MModelManager::SetDevice(FDevice& Device)
	{
		MModelManager::Device = &Device;
	}


// Static Variables:

	FDevice* MModelManager::Device;

}