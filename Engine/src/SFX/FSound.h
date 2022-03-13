#pragma once

#include "ESound.h"
#include "ESoundGroup.h"
#include "../Templates/TArray.h"
#include "../Events/IEventListener.h"

namespace t3d
{
	class FSound : public IEventListener
	{
	public:

	// Functions:

		static void    Initialize     (float32 InitialVolume);
		static void    LoadFile       (ESound Name, const std::string& FilePath);
		static FSound* GetInstance    ();		
		static void    Update         (); // Pass global DeltaTime here.
		static void    Shutdown       ();

	// IEventListener Interface:

		void OnEvent(const FEvent* const Event) override;

	// Accessors:

		const float32& GetVolume();

	// Modifiers:

		/// <param name="Volume"> : Value in range between 0.0 and 1.0 </param>
		void SetVolume(float32 Volume);

	private:

	// Private Functions:

		void Play        (ESound Name, ESoundGroup Group);
		void Pause       ();
		void Pause       (ESoundGroup Group);
		void Unpause     ();
		void Unpause     (ESoundGroup Group);

	// Private Constructors and Destructor:

		FSound  ();
		~FSound ();

		T3D_NO_COPY(FSound);
		T3D_NO_MOVE(FSound);

	// Instance:

		static FSound Instance;

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
	};
}