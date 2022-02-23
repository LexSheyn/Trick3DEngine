#pragma once

#include "IComponent.h"

namespace t3d
{
	template<class C>
	class TComponent : public IComponent
	{
	public:

	// IComponent Interface Functions:

		virtual void ConstructData(uint8* Data) const override
		{
			new (&Data[0]) C();
		}

		virtual void MoveData(uint8* Source, uint8* Destination) const override
		{
			new (&Destination[0]) C(std::move(*reinterpret_cast<C*>(Source)));
		}

		virtual void DestroyData(uint8* Data) const override
		{
			C* DataLocation = std::launder(reinterpret_cast<C*>(Data));

			DataLocation->~C();
		}

	// IComponent Interface Accessors:

		virtual size_t GetSize() const override
		{
			return sizeof(C);
		}

	// Accessors:

		static T3D_ComponentTypeID GetTypeID()
		{
			return TTypeIDGenerator<IComponent>::GetNewID<C>();
		}
	};
}