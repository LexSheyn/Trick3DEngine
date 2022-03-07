#pragma once

#include "ECSComponent.h"

namespace t3d
{
	class BaseECSSystem
	{
	public:

		enum Flags : uint32
		{
			None     = 0,
			Optional = 1
		};

		BaseECSSystem() {}

		virtual void UpdateComponents(float32 DeltaTime, BaseECSComponent** Components) {}

		const std::vector<uint64>& GetComponentTypes() const { return ComponentTypes; }

		const std::vector<BaseECSSystem::Flags>&  GetComponentFlags() const { return ComponentFlags; }

		bool8 IsValid() const
		{
			for (uint64 i = 0u; i < ComponentFlags.size(); i++)
			{
				if ((ComponentFlags[i] & BaseECSSystem::Flags::Optional) == 0)
				{
					return true;
				}
			}

			return false;
		}

	protected:

		void AddComponentType(uint64 ComponentType, BaseECSSystem::Flags ComponentFlag = BaseECSSystem::Flags::None)
		{
			ComponentTypes.push_back(ComponentType);

			ComponentFlags.push_back(ComponentFlag);
		}

	private:

		std::vector<uint64> ComponentTypes;
		std::vector<BaseECSSystem::Flags>  ComponentFlags;
	};

	class ECSSystemList
	{
	public:

		bool8 AddSystem(BaseECSSystem& System)
		{
			if (!System.IsValid())
			{
				return false;
			}

			Systems.push_back(&System);

			return true;
		}

		bool8 RemoveSystem(BaseECSSystem& System)
		{
			for (uint64 i = 0u; i < Systems.size(); i++)
			{
				if (&System == Systems[i])
				{
					Systems.erase(Systems.begin() + i);

					return true;
				}
			}

			return false;
		}

		uint64 Size() const { return Systems.size(); }

		BaseECSSystem* operator [] (uint64 Index) { return Systems[Index]; }

	private:

		std::vector<BaseECSSystem*> Systems;
	};
}