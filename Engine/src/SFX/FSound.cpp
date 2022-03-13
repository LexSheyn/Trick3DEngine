#include "../PrecompiledHeaders/t3dpch.h"
#include "FSound.h"

namespace t3d
{
// Functions:

	void FSound::Initialize(float32 InitialVolume)
	{
	// Volume:

		Instance.Volume = InitialVolume;

	// System:

		FMOD::System_Create(&Instance.System);

		Instance.System->init(static_cast<int>(Instance.Channels.Size()), FMOD_DEFAULT, nullptr);

	// Channel groupds:

		Instance.System->createChannelGroup("UI", &Instance.Groups[ESoundGroup::UI]);

		Instance.System->getMasterChannelGroup(&Instance.MasterGroup);

		Instance.MasterGroup->addGroup(Instance.Groups[ESoundGroup::UI]);

		for (uint64 i = 0u; i < Instance.Channels.Size(); i++)
		{
			Instance.Channels[i]->setChannelGroup(Instance.Groups[ESoundGroup::UI]);
		}

		Instance.MasterGroup->setVolume(Instance.Volume);
	}

	void FSound::LoadFile(ESound Name, const std::string& FilePath)
	{
		Instance.System->createSound(FilePath.c_str(), FMOD_DEFAULT, nullptr, &Instance.Sounds[Name]);
	}

	FSound* FSound::GetInstance()
	{
		return &Instance;
	}

	void FSound::Update()
	{
		Instance.System->update();
	}

	void FSound::Shutdown()
	{
		Instance.MasterGroup->stop();

		for (uint64 i = 0u; i < Instance.Channels.Size(); i++)
		{
			Instance.Sounds[i]->release();
		}

		Instance.System->close();
		Instance.System->release();
	}


// IEventListener Interface:

	void FSound::OnEvent(const FEvent* const Event)
	{
		if (Event->GetType() == EEventType::KeyPressed)
		{
			Instance.Play(ESound::KeyPress, ESoundGroup::UI);
		}
		else if (Event->GetType() == EEventType::KeyReleased)
		{
			Instance.Play(ESound::KeyRelease, ESoundGroup::UI);
		}
	}


// Accessors:

	const float32& FSound::GetVolume()
	{
		return Volume;
	}


// Modifiers:

	void FSound::SetVolume(float32 Volume)
	{
		if (Volume < VolumeMin)
		{
			this->Volume = VolumeMin;
		}
		else if (Volume > VolumeMax)
		{
			this->Volume = VolumeMax;
		}
		else
		{
			this->Volume = Volume;
		}
	}


// Private Functions:

	void FSound::Play(ESound Name, ESoundGroup Group)
	{
		System->playSound(Sounds[Name], Groups[Group], false, &Channels[Name]);
	}

	void FSound::Pause()
	{
		MasterGroup->setPaused(true);
	}

	void FSound::Pause(ESoundGroup Group)
	{
		Groups[Group]->setPaused(true);
	}

	void FSound::Unpause()
	{
		MasterGroup->setPaused(false);
	}

	void FSound::Unpause(ESoundGroup Group)
	{
		Groups[Group]->setPaused(false);
	}


// Private Constructors and Destructor:

	FSound::FSound()
	{
	// System:

		System = nullptr;

	// Sounds:

		for (uint64 i = 0u; i < Sounds.Size(); i++)
		{
			Sounds[i] = nullptr;
		}

	// Channels:

		for (uint64 i = 0u; i < Channels.Size(); i++)
		{
			Channels[i] = nullptr;
		}

	// Groups
		
		for (uint64 i = 0u; i < Groups.Size(); i++)
		{
			Groups[i] = nullptr;
		}

		MasterGroup = nullptr;

	// Volume:

		Volume = 0.0f;
	}

	FSound::~FSound()
	{
	}


// Static Variables:

	FSound FSound::Instance;
}