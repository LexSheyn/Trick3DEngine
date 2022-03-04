#pragma once

#include "FEntity.h"
#include "../Components/IComponent.h"
#include "../Systems/IComponentSystem.h"

#include "../Components/EComponentType.h"

namespace t3d
{
//	class C
//	{
//	public:
//		static EComponentType Type;
//	};
//
//	class FEntityManager
//	{
//	public:
//
//	// Constructors and Destructor:
//
//		FEntityManager(const FEntityManager&) = delete;
//
//		FEntityManager(FEntityManager&&) = delete;
//
//		~FEntityManager() {}
//
//	// Operators:
//
//		FEntityManager& operator=(const FEntityManager&) = delete;
//
//		FEntityManager& operator=(FEntityManager&&) = delete;
//
//	// Entity Functions:
//
//		void CreateEntity()
//		{
//			// To do...
//		}
//
//		void RemoveEntity()
//		{
//			// To do...
//		}
//
//	// Component Functions:
//
//		template<class C>
//		void AddComponent(T3D_EntityID ID)
//		{
//			Components[C::Type][ID] = C();
//		}
//
//		template<class C>
//		void RemoveComponent(T3D_EntityID ID)
//		{
//			Components.at(C::Type).erase(ID);
//		}
//
//		template<class C>
//		bool8 HasComponent(T3D_EntityID ID)
//		{
//			return Components.at(C::Type).contains(ID);
//		}
//
//		template<class C>
//		C* GetComponent(T3D_EntityID ID)
//		{
//			return &Components.at(C::Type).at(ID);
//		}
//
//	private:
//
//	// Private Default Constructor:
//
//		FEntityManager() {}
//
//	// Variables:
//
//		static std::unordered_set<T3D_EntityID> Entities;
//
//		static std::unordered_map<EComponentType, std::unordered_map<T3D_EntityID, IComponent>> Components;
//
//		static std::unordered_map<EComponentType, IComponentSystem> Systems;
//	};
}