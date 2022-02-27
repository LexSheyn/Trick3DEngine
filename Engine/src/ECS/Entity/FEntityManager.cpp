#include "../../Precompiledheaders/t3dpch.h"
#include "FEntityManager.h"

namespace t3d
{
// Constructors and Destructor:

	FEntityManager::FEntityManager()
	{
		// To do: Temporary -> Create some test things.
	}

	FEntityManager::~FEntityManager()
	{
		// To do: Delete components here!
	}


// Fumctions:

	void FEntityManager::CreateSystems()
	{
	}

	void FEntityManager::Update()
	{
	}

	T3D_EntityID FEntityManager::CreateEntity()
	{
		return T3D_EntityID();
	}

	void FEntityManager::DestroyEntity(const T3D_EntityID& EntityID)
	{
	}

}