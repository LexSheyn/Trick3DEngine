#pragma once

#include "IObject.h"

#include "../Render/Primitives/Mesh/FMesh.h"

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

	// Constructors and Destructor:

		OGameObject();

		OGameObject(const OGameObject&) = delete;

		// Move constructor.
		OGameObject(OGameObject&&) = default;

		~OGameObject();

	// Operators:

		OGameObject& operator=(const OGameObject&) = delete;

		// Move operator.
		OGameObject& operator=(OGameObject&&) = default;

	// Functions:

		//

	// Accessors:

		T3D_INLINE const uint32& GetID() const { return ID; }

		T3D_INLINE CTransform3DComponent& GetTransform() { return Transform; }

	//	T3D_INLINE FMesh*& GetMesh() { return Mesh; }

	// Modifiers:

		//

	private:

	// Variables:

		uint32 ID{};

	// Components:

	//TEST
	public:

		glm::vec3 Color{};

	// TEST
//	private:

		CTransform3DComponent Transform;

	// TEST
	public:

		FMesh* Mesh;

	// TEST
	public:

		float32 LightIntensity = 0.0f;

		int Light = 0;
	};
}