#pragma once

#include "../ECS/Systems/ISystem.h"
#include "ESound.h"
#include "ESoundGroup.h"
#include "../Input/Keyboard/FKey.h"
#include "../Input/Keyboard/FKeystate.h"
#include "../Templates/TArray.h"
#include "../Events/Experimental/SEvent.h"

namespace t3d
{
	class FSoundSystem : public ISystem
	{
	public:

	// Constructors and Destructor:

		 FSoundSystem    ();
		~FSoundSystem    ();

	// ISystem Interface:

		void OnLateUpdate    () override;

	// Accessors:

		const float32& GetVolume    ();

	// Modifiers:

		/// <param name="Volume"> : Value in range between 0.0 and 1.0 </param>
		void SetVolume    (float32 Volume);

	private:

	// Private Functions:

		void Initialize    (float32 InitialVolume);
		void LoadFile      (ESound Name, const std::string& FilePath);	
		void Shutdown      ();
		void Play          (ESound Name, ESoundGroup Group);
		void Pause         ();
		void Pause         (ESoundGroup Group);
		void Unpause       ();
		void Unpause       (ESoundGroup Group);

	// System:

		FMOD::System* System;

	// Sounds and Channels:

		static constexpr uint64 ChannelsMax = 32;

		TArray<FMOD::Sound*,   ChannelsMax> Sounds;

		TArray<FMOD::Channel*, ChannelsMax> Channels;

	// Channel groups:

		static constexpr uint64 GroupsMax = static_cast<uint64>(ESoundGroup::MAX);

		TArray<FMOD::ChannelGroup*, GroupsMax> Groups;

		FMOD::ChannelGroup* MasterGroup;

	// Variables:

		static constexpr float32 VolumeMin = 0.0f;
		static constexpr float32 VolumeMax = 1.0f;
		float32 Volume;

	// Event Callbacks:

		static bool8 T3D_CALL OnKeyPress            (FObject Instance, const FKeyData& Data);
		static bool8 T3D_CALL OnKeyRelease          (FObject Instance, const FKeyData& Data);
		static bool8 T3D_CALL OnMouseButtonPress    (FObject Instance, const FMouseButtonData& Data);
	};
}