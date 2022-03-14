#pragma once

#include "FScene.h"
#include "EScene.h"
#include "../Templates/TArray.h"

namespace t3d
{
	class MSceneManager : public IEventListener
	{
	public:

	// Constructors and Destructor:

		 MSceneManager ();
		~MSceneManager ();

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

	public:

	// IEventListener Interface:

		void OnEvent(const FEvent* const Event) override;
	};
}