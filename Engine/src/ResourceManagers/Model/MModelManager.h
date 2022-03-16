#pragma once

namespace t3d
{
	class MModelManager
	{
	public:

	// Functions:

		static class FMesh* T3D_CALL LoadModel    (const std::string& FilePath);

	// Modifiers:

		static void T3D_CALL SetDevice(class FDevice& Device);

	private:

	// Private Construcor and Destructor:

		 MModelManager () {}
		~MModelManager () {}

		T3D_NO_COPY(MModelManager);
		T3D_NO_MOVE(MModelManager);

	// Variables:

		static class FDevice* Device;

	// Resource storage:

		// To do...
		//  std::vector<uint8>
	};
}