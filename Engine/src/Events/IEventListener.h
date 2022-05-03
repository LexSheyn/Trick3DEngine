#pragma once

namespace t3d
{
	class IEventListener
	{
	public:

	// Interface:

		virtual void OnEvent    (const class FEvent* const Event) = 0;

	// Accessors:

		const uint64& GetId    () const;

	protected:

	// Protected Constructors and Destructor:

		         IEventListener();
		virtual ~IEventListener();

	private:

	// Variables:

		uint64 Id;
	};
}