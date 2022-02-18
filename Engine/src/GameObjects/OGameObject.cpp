#include "../PrecompiledHeaders/t3dpch.h"
#include "OGameObject.h"

namespace t3d
{
// Destructor:

	OGameObject::~OGameObject()
	{
		Mesh = nullptr;
	}


// Functions:

	OGameObject OGameObject::Create()
	{
		static uint32 CurrentID = 0u;

		return OGameObject(CurrentID++);
	}

	OGameObject OGameObject::MakePointLight(float32 Intensity, float32 Radius, glm::vec3 Color)
	{
		OGameObject GameObject = OGameObject::Create();

		GameObject.Color                      = Color;
		GameObject.GetTransform().SetScale({ Radius, 0.0f, 0.0f });
		GameObject.PointLight                 = std::make_unique<FPointLightComponent>();
		GameObject.PointLight->LightIntensity = Intensity;

		return GameObject;
	}


// Private Constructor:

	OGameObject::OGameObject(uint32 ObjectID)
		: ID(ObjectID),
		  Color(glm::vec3(1.0f))//,
		 // Mesh(nullptr)
	{
	}
}