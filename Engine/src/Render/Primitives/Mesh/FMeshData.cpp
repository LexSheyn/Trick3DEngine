#include "../../../PrecompiledHeaders/t3dpch.h"
#include "FMeshData.h"

// Tiny OBJ loader:
#include "../../../ThirdParty/tiny_obj_loader.h"

// Disable warnings from tiny_obj_loader:
#pragma warning( push ) // tiny_obj_loader - Begin
#pragma warning( disable : 26495 ) // Uninitialized variable.
#pragma warning( disable : 26451 ) // Arithmetic overflow.
#pragma warning( disable : 26498 ) // constexpr.

namespace t3d
{
// Constructors and Destructor:

	FMeshData::FMeshData()
	{
	}

	FMeshData::FMeshData(const std::vector<FVertex>& Vertices, const std::vector<uint32>& Indices)
		: Vertices(Vertices),
		  Indices(Indices)
	{
	}

	FMeshData::~FMeshData()
	{
	}


// Functions:

	void FMeshData::LoadOBJ(const std::string& FilePath)
	{
		tinyobj::attrib_t Attributes;

		std::vector<tinyobj::shape_t> Shapes;

		std::vector<tinyobj::material_t> Materials;

		std::string Warning;
		std::string Error;

		if (!tinyobj::LoadObj(&Attributes, &Shapes, &Materials, &Warning, &Error, FilePath.c_str()))
		{
			LOG_ERROR(Warning + Error);
			throw;
		}

		Vertices.clear();
		Indices.clear();

		std::unordered_map<FVertex, uint32> UniqueVertices;

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

					Vertex.Color =
					{
						Attributes.colors[3 * Index.vertex_index + 0],
						Attributes.colors[3 * Index.vertex_index + 1],
						Attributes.colors[3 * Index.vertex_index + 2]
					};
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
					UniqueVertices[Vertex] = static_cast<uint32>(Vertices.size());

					Vertices.push_back(Vertex);
				}

				Indices.push_back(UniqueVertices[Vertex]);
			}
		}
	}

}

#pragma warning( pop ) // tiny_obj_loader - End