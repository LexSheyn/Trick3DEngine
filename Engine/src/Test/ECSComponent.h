#pragma once

#include "BaseECSComponent.h"
#include "../Types/T3DTypes.h"
#include "../Templates/TTypeID.h"

namespace t3d
{
	template<typename ComponentType>
	struct ECSComponent : public BaseECSComponent
	{
		static const ECSComponentCreateFunction CreateFunction;
	
		static const ECSComponentFreeFunction FreeFunction;

		static const uint64 Size;

		static const uint64 ID;
	};

// Functions:

	template<typename ComponentType>
	uint64 ECSComponentCreate(std::vector<uint8>& Memory, EntityHandle Entity, BaseECSComponent* ComponentPtr)
	{
		uint64 Index = Memory.size();

		Memory.resize(Index + ComponentType::Size);

		ComponentType* Component = new(&Memory[Index]) ComponentType( *(static_cast<ComponentType*>(ComponentPtr)) );

		Component->Entity = Entity;

		return Index;
	}

	// Pointless, does not work.
	template<typename ComponentType>
	void ECSComponentFree(BaseECSComponent* ComponentPtr)
	{
		ComponentType* Component = static_cast<ComponentType*>(ComponentPtr);

		Component->~ComponentType(); // Pointless, does not work.
	}


// Variables:

	template<typename ComponentType>
	const BaseECSComponent::ECSComponentCreateFunction ECSComponent<ComponentType>::CreateFunction = ECSComponentCreate<ComponentType>;

	template<typename ComponentType>
	const BaseECSComponent::ECSComponentFreeFunction ECSComponent<ComponentType>::FreeFunction = ECSComponentFree<ComponentType>;

	template<typename ComponentType>
	const uint64 ECSComponent<ComponentType>::Size = sizeof(ComponentType);

	template<typename ComponentType>
	const uint64 ECSComponent<ComponentType>::ID = BaseECSComponent::RegisterComponentType(ECSComponent<ComponentType>::CreateFunction, ECSComponent<ComponentType>::FreeFunction, ECSComponent<ComponentType>::Size);
//	const uint64 ECSComponent<ComponentType>::ID = TTypeID<ComponentType>::GetID();




// TEST

//	template<typename ComponentType>
//	ComponentType* ECSComponentCreate(std::vector<uint8>& Memory, EntityHandle Entity)
//	{
//		uint64 Index = Memory.size();
//
//		Memory.resize(Index + ComponentType::Size);
//
//		ComponentType* Component = new(&Memory[Index]) ComponentType();
//
//		Component->Entity = Entity;
//
//		return Component;
//	}
//
//	template<typename ComponentType>
//	void ECSComponentFree(BaseECSComponent& ComponentPtr)
//	{
//		ComponentType& Component = static_cast<ComponentType&>(ComponentPtr);
//
//		Component.~ComponentType();
//	}
}