#pragma once

namespace t3d
{
	class IEventListener
	{
	public:

	// Constructors and Destructor:

		IEventListener();

		virtual ~IEventListener();

	// Functions:

		virtual void OnEvent(const class FEvent* const Event) = 0;

	// Accessors:

		const uint32& GetID() const;

	private:

	// Variables:

		uint32 ID;
	};
}