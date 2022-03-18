#pragma once

namespace t3d
{
	class ISystem
	{
	public:

	// Interface:

		virtual void Update() = 0;

	protected:

	// Protected Constructors and Destructor:

		         ISystem() {}
		virtual ~ISystem() {}

		T3D_NO_COPY(ISystem);
		T3D_NO_MOVE(ISystem);
	};
}