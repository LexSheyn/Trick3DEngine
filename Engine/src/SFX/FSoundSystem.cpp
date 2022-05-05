#include "../PCH/t3dpch.h"
#include "FSoundSystem.h"

namespace t3d
{
// Constructors and Destructor:

	FSoundSystem::FSoundSystem()
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

		FSoundSystem::Initialize(0.4f);
		FSoundSystem::LoadFile(ESound::KeyPress  , "D:/Royalty FREE Music/ZapSplat/SFX/zapsplat_multimedia_button_click_001_78078.mp3");
		FSoundSystem::LoadFile(ESound::KeyRelease, "D:/Royalty FREE Music/ZapSplat/SFX/zapsplat_multimedia_button_click_002_78079.mp3");

	// Events:

		SEvent::KeyPress.Subscribe(this, OnKeyPress);
		SEvent::KeyRelease.Subscribe(this, OnKeyRelease);
		SEvent::MouseButtonPress.Subscribe(this, OnMouseButtonPress);
	}

	FSoundSystem::~FSoundSystem()
	{
		SEvent::KeyPress.Unsubscribe(OnKeyPress);
		SEvent::KeyRelease.Unsubscribe(OnKeyRelease);
		SEvent::MouseButtonPress.Unsubscribe(OnMouseButtonPress);

		FSoundSystem::Shutdown();
	}


// Functions:

	void FSoundSystem::Update()
	{
		System->update();
	}


// Accessors:

	const float32& FSoundSystem::GetVolume()
	{
		return Volume;
	}


// Modifiers:

	void FSoundSystem::SetVolume(float32 Volume)
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

	void FSoundSystem::Initialize(float32 InitialVolume)
	{
	// Volume:

		Volume = InitialVolume;

	// System:

		FMOD::System_Create(&System);

		System->init(static_cast<int>(Channels.Size()), FMOD_DEFAULT, nullptr);

	// Channel groupds:

		System->createChannelGroup("UI", &Groups[ESoundGroup::UI]);

		System->getMasterChannelGroup(&MasterGroup);

		MasterGroup->addGroup(Groups[ESoundGroup::UI]);

		for (uint64 i = 0u; i < Channels.Size(); i++)
		{
			Channels[i]->setChannelGroup(Groups[ESoundGroup::UI]);
		}

		MasterGroup->setVolume(Volume);
	}

	void FSoundSystem::LoadFile(ESound Name, const std::string& FilePath)
	{
		System->createSound(FilePath.c_str(), FMOD_DEFAULT, nullptr, &Sounds[Name]);
	}

	void FSoundSystem::Shutdown()
	{
		MasterGroup->stop();

		for (uint64 i = 0u; i < Channels.Size(); i++)
		{
			Sounds[i]->release();
		}

		System->close();
		System->release();
	}

	void FSoundSystem::Play(ESound Name, ESoundGroup Group)
	{
		System->playSound(Sounds[Name], Groups[Group], false, &Channels[Name]);
	}

	void FSoundSystem::Pause()
	{
		MasterGroup->setPaused(true);
	}

	void FSoundSystem::Pause(ESoundGroup Group)
	{
		Groups[Group]->setPaused(true);
	}

	void FSoundSystem::Unpause()
	{
		MasterGroup->setPaused(false);
	}

	void FSoundSystem::Unpause(ESoundGroup Group)
	{
		Groups[Group]->setPaused(false);
	}


// Event Callbacks:

	bool8 FSoundSystem::OnKeyPress(FObject Instance, const FKeyData& Data)
	{
		Instance.Get<FSoundSystem>()->Play(ESound::KeyPress, ESoundGroup::UI);

		return true;
	}

	bool8 FSoundSystem::OnKeyRelease(FObject Instance, const FKeyData& Data)
	{
		Instance.Get<FSoundSystem>()->Play(ESound::KeyRelease, ESoundGroup::UI);

		return true;
	}

	bool8 FSoundSystem::OnMouseButtonPress(FObject Instance, const FMouseButtonData& Data)
	{
		Instance.Get<FSoundSystem>()->Play(ESound::KeyPress, ESoundGroup::UI);

		return true;
	}

}