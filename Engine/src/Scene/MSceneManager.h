#pragma once

#include "FScene.h"
#include "EScene.h"

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

		void T3D_CALL SetActive    (EScene Name);
		void T3D_CALL Update       ();

	// Accessors:

		FScene& GetActiveScene();

	private:

	// Private Functions:

		void T3D_CALL LoadScene       (EScene Name);
		void T3D_CALL UnloadScene     (EScene Name);
		void T3D_CALL LoadFromFile    (EScene Name);
		void T3D_CALL SaveToFile      (EScene Name);

	// Variables:

		EScene ActiveScene;

		TArray<FScene, 1> Scenes;

	public:

	// IEventListener Interface:

		void T3D_CALL OnEvent(const FEvent* const Event) override;
	};
}