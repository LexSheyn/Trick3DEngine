#include "../PrecompiledHeaders/t3dpch.h"
#include "BaseECSComponent.h"

namespace t3d
{
// Functions:

    uint64 t3d::BaseECSComponent::RegisterComponentType(ECSComponentCreateFunction CreateFunction, ECSComponentFreeFunction FreeFunction, uint64 Size)
    {
        uint64 ComponentID = Size;

        ComponentTypes.push_back(std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, uint64>(CreateFunction, FreeFunction, Size));

        return ComponentID;
    }

    std::vector< std::tuple<BaseECSComponent::ECSComponentCreateFunction, BaseECSComponent::ECSComponentFreeFunction, uint64> > BaseECSComponent::ComponentTypes;
}