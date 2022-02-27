#pragma once

namespace t3d
{
	class IComponentSystem
	{
	public:

	// Constructors and Destructor:

		IComponentSystem() {}

		virtual ~IComponentSystem() {}

	// Intarface:

		virtual bool8 Initialize() = 0;

		virtual void  Update()     = 0; // Requires global DeltaTime!
	};
}