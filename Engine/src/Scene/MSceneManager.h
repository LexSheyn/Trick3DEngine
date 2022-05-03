#pragma once

#include "FScene.h"
#include "EScene.h"
#include "../Templates/TArray.h"
#include "../Events/Experimental/SEvent.h"

namespace t3d
{
	class MSceneManager
	{
	public:

	// Constructors and Destructor:

		 MSceneManager    ();
		~MSceneManager    ();

		T3D_NO_COPY(MSceneManager);
		T3D_NO_MOVE(MSceneManager);

	// Functions:

		void SetActive    (EScene Name);
		void Update       ();

	// Accessors:

		FScene& GetActiveScene();

	private:

	// Private Functions:

		void LoadScene       (EScene Name);
		void UnloadScene     (EScene Name);
		void LoadFromFile    (EScene Name);
		void SaveToFile      (EScene Name);

	// Variables:

		EScene ActiveScene;

		TArray<FScene, 1> Scenes;

	// Event Callbacks:

		static bool8 OnFramebufferSize    (FObject Instance, const FFramebufferSizeData& Data);
		static bool8 OnKeyPress           (FObject Instance, const FKeyData& Data);
	};
}