#pragma once

#include "IObject.h"

#include "../Render/Objects/Mesh/FMesh.h"

#include "../Components/CTransform3DComponent.h"

struct FPointLightComponent
{
	float32 LightIntensity = 1.0f;
};

namespace t3d
{
	class OGameObject : public IObject
	{
	public:

	// Constructors:

		OGameObject() {};

		OGameObject(const OGameObject&) = delete;

		// Move constructor.
		OGameObject(OGameObject&&) = default;

		~OGameObject();

	// Operators:

		OGameObject& operator=(const OGameObject&) = delete;

		// Move operator.
		OGameObject& operator=(OGameObject&&) = default;

	// Functions:

		static OGameObject Create();

		static OGameObject MakePointLight(float32 Intensity = 10.0f, float32 Radius = 0.05f, glm::vec3 Color = glm::vec3(1.0f));

	// Accessors:

		T3D_INLINE const uint32& GetID() const { return ID; }

		T3D_INLINE CTransform3DComponent& GetTransform() { return Transform; }

	//	T3D_INLINE FMesh*& GetMesh() { return Mesh; }

	// Modifiers:

		//

	private:

	// Private Constructor:

		OGameObject(uint32 ObjectID);

	// Variables:

		uint32 ID{};

	// Components:

	//TEST
	public:

		glm::vec3 Color{};

	// TEST
	private:

		CTransform3DComponent Transform;

	// TEST
	public:

		std::shared_ptr<FMesh> Mesh;

	// TEST
	public:

		std::unique_ptr<FPointLightComponent> PointLight;		
	};
}