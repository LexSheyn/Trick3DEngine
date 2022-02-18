#pragma once

namespace t3d
{
	class IEventListener
	{
	public:

	// Constructors and Destructor:

		IEventListener()
		{
			static int32 ID = 0u;

			this->ID = ID++;
		}

		virtual ~IEventListener() {};

	// Functions:

		virtual void OnEvent(const class FEvent* const Event) = 0;

	// Accessors:

		T3D_INLINE const uint32& GetID() const { return ID; }

	private:

	// Variables:

		uint32 ID;
	};
}