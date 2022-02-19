#include "../PrecompiledHeaders/t3dpch.h"
#include "OGameObject.h"

namespace t3d
{
// Constructors and Destructor:

	OGameObject::OGameObject()
		: ID(),
		  Color(glm::vec3(1.0f)),
		  Mesh(nullptr)
	{
		static uint32 CurrentID = 0u;

		ID = CurrentID++;
	}

	OGameObject::~OGameObject()
	{
	}


// Functions:


}