#pragma once

#include "ESound.h"
#include "ESoundGroup.h"
#include "../Templates/TArray.h"

namespace t3d
{
	class FSound
	{
	public:

	// Functions:

		static void InitSystem	    (float32 InitialVolume);
		static void Load            (ESound Name, const std::string& FilePath);
		static void Play		    (ESound Name, ESoundGroup Group);
		static void Pause		    (ESoundGroup Group = ESoundGroup::Master);
		static void Unpause		    (ESoundGroup Group = ESoundGroup::Master);
		static void Update		    (); // Pass global DeltaTime here.
		static void Shutdown	    ();

	// Accessors:

		static const float32& GetVolume();

	// Modifiers:

		/// <param name="Value"> : Volume in range between 0.0 and 1.0 </param>
		static void SetVolume(float32 Value);

	private:

	// Private Constructors and Destructor:

		FSound  () {}
		~FSound () {}

		T3D_NO_COPY(FSound);
		T3D_NO_MOVE(FSound);

	// System:

		static FMOD::System* System;

	// Sounds and Channels:

		static constexpr uint64 ChannelsMax = 32;

		static TArray<FMOD::Sound*,   ChannelsMax> Sounds;

		static TArray<FMOD::Channel*, ChannelsMax> Channels;

	// Channel groups:

		static constexpr uint64 GroupsMax = static_cast<uint64>(ESoundGroup::MAX);

		static TArray<FMOD::ChannelGroup*, GroupsMax> Groups;

	// Variables:

		static constexpr float32 VolumeMin = 0.0f;
		static constexpr float32 VolumeMax = 1.0f;
		static float32 Volume;
	};
}