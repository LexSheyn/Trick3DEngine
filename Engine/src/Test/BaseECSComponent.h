#pragma once

typedef void* EntityHandle;

#define ENTITY_NULL_HANDLE nullptr

namespace t3d
{
	struct BaseECSComponent
	{
	public:

		typedef uint64 (*ECSComponentCreateFunction) (std::vector<uint8>&, EntityHandle, BaseECSComponent*);

		typedef void (*ECSComponentFreeFunction) (BaseECSComponent*);

	// Functions:

		static uint64 RegisterComponentType(ECSComponentCreateFunction CreateFunction, ECSComponentFreeFunction FreeFunction, uint64 Size);

		inline static ECSComponentCreateFunction GetTypeCreateFunction(uint64 ID)
		{
			return std::get<0>(ComponentTypes[ID]);
		}

		inline static ECSComponentFreeFunction GetTypeFreeFunction(uint64 ID)
		{
			return std::get<1>(ComponentTypes[ID]);
		}

		inline static uint64 GetTypeSize(uint64 ID)
		{
			return std::get<2>(ComponentTypes[ID]);
		}

		inline static bool8 IsTypeValid(uint64 ID)
		{
			return ID < ComponentTypes.size();
		}

	// Variables:

		EntityHandle Entity = ENTITY_NULL_HANDLE;

	private:

		static std::vector< std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, uint64> > ComponentTypes;
	};

}