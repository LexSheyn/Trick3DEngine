#pragma once

#include "FScene.h"
#include "EScene.h"
#include "../Events/Experimental/IEventListenerEx.h"

namespace t3d
{
	class MSceneManager : IEventListener, IEventListenerEx
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

	public:

	// IEventListener Interface:

		void OnEvent    (const FEvent* const Event) override;

		static bool8 OnKeyPress    (void* Instance, const FKeyData& Data);
	};
}