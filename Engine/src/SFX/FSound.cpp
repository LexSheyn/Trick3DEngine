#include "../PrecompiledHeaders/t3dpch.h"
#include "FSound.h"

namespace t3d
{
// Functions:

	void FSound::InitSystem(float32 InitialVolume)
	{
	// Volume:

		Volume = InitialVolume;

	// System:

		FMOD::System_Create(&System);

		System->init(static_cast<int>(Channels.Size()), FMOD_DEFAULT, nullptr);

	// Channel groupds:

		System->createChannelGroup("UI", &Groups[ESoundGroup::UI]);

		System->getMasterChannelGroup(&Groups[ESoundGroup::Master]);

		Groups[ESoundGroup::Master]->addGroup(Groups[ESoundGroup::UI]);

		for (uint64 i = 0u; i < Channels.Size(); i++)
		{
			Channels[i]->setChannelGroup(Groups[ESoundGroup::UI]);
		}

		Groups[ESoundGroup::Master]->setVolume(Volume);
	}

	void FSound::Load(ESound Name, const std::string& FilePath)
	{
		System->createSound(FilePath.c_str(), FMOD_DEFAULT, nullptr, &Sounds[Name]);
	}

	void FSound::Play(ESound Name, ESoundGroup Group)
	{
		System->playSound(Sounds[Name], Groups[Group], false, &Channels[Name]);
	}

	void FSound::Pause(ESoundGroup Group)
	{
		Groups[Group]->setPaused(true);
	}

	void FSound::Unpause(ESoundGroup Group)
	{
		Groups[Group]->setPaused(false);
	}

	void FSound::Update()
	{
		System->update();
	}

	void FSound::Shutdown()
	{
		Groups[ESoundGroup::Master]->stop();

		for (uint64 i = 0u; i < Channels.Size(); i++)
		{
			Sounds[i]->release();
		}

		System->close();
		System->release();
	}


// Accessors:

	const float32& FSound::GetVolume()
	{
		return Volume;
	}


// Modifiers:

	void FSound::SetVolume(float32 Value)
	{
		if (Value < VolumeMin)
		{
			Volume = VolumeMin;
		}
		else if (Value > VolumeMax)
		{
			Volume = VolumeMax;
		}
		else
		{
			Volume = Value;
		}
	}


// Static Variables:

	// System:

	FMOD::System* FSound::System;

	// Sounds and Channels:

//	constexpr uint64 FSound::ChannelsMax = 32;

	TArray<FMOD::Sound*, FSound::ChannelsMax> FSound::Sounds;

	TArray<FMOD::Channel*, FSound::ChannelsMax> FSound::Channels;

	// Channel groups:

//	constexpr uint64 FSound::GroupsMax = static_cast<uint64>(ESoundGroup::MAX);

	TArray<FMOD::ChannelGroup*, FSound::GroupsMax> FSound::Groups;

	// Variables:

//	constexpr float32 FSound::VolumeMin = 0.0f;
//	constexpr float32 FSound::VolumeMax = 1.0f;
	float32 FSound::Volume;
}