#include "stdafx.h"
#include "AudioManager.h"

AudioManager AudioManager::myInstance;

AudioManager::AudioManager()
{
	myMusicEngine = irrklang::createIrrKlangDevice();
	myEffectEngine = irrklang::createIrrKlangDevice();
}

AudioManager::~AudioManager()
{
	myMusicEngine->drop();
	myEffectEngine->drop();
}

void AudioManager::PlayMusic(const char* aPath)
{
	myMusicEngine->play2D(aPath);
}

void AudioManager::PlayMusic(const char* aPath, bool aLooping)
{
	myMusicEngine->play2D(aPath, aLooping);
}

void AudioManager::PlayMusic(const char* aPath, bool aLooping, float volume)
{
	irrklang::ISoundSource* sound = myMusicEngine->addSoundSourceFromFile(aPath);

	if (sound != nullptr)
	{
		sound->setDefaultVolume(volume);

		myMusicEngine->play2D(sound, aLooping, false, false);

	}
	else
	{
		myMusicEngine->play2D(myMusicEngine->getSoundSource(aPath), aLooping, false, false);
	}
}

void AudioManager::PlayEffect(const char* aPath)
{
	myEffectEngine->play2D(aPath);
}

void AudioManager::PlayEffect(const char* aPath, bool aLooping)
{
	myEffectEngine->play2D(aPath, aLooping);
}

void AudioManager::PlayEffect(const char* aPath, bool aLooping, float volume)
{
	irrklang::ISoundSource* sound = myEffectEngine->addSoundSourceFromFile(aPath);

	if (sound != nullptr)
	{
		sound->setDefaultVolume(volume);
		myEffectEngine->play2D(sound, aLooping, false, true);
	}
	else
	{
		myEffectEngine->play2D(myEffectEngine->getSoundSource(aPath), aLooping, false, false);
	}
}

void AudioManager::StopAllMusic()
{
	myMusicEngine->stopAllSounds();
}

void AudioManager::StopAllEffects()
{
	myEffectEngine->stopAllSounds();
}

void AudioManager::StopMusicSound(const char* aPath)
{
	if (myMusicEngine->getSoundSource(aPath) != nullptr)
	{
		myMusicEngine->stopAllSoundsOfSoundSource(myMusicEngine->getSoundSource(aPath));
	}
}

void AudioManager::StopEffectSound(const char* aPath)
{
	if (myEffectEngine->getSoundSource(aPath) != nullptr)
	{
		myEffectEngine->stopAllSoundsOfSoundSource(myEffectEngine->getSoundSource(aPath));
	}
}

void AudioManager::RemoveFileFromMusicEngine(const char* aPath)
{
	if (myMusicEngine->getSoundSource(aPath) != nullptr)
	{
		myMusicEngine->removeSoundSource(myMusicEngine->getSoundSource(aPath));
	}
}

void AudioManager::RemoveAllAudioFromMusicEngine()
{
	myMusicEngine->removeAllSoundSources();
}

void AudioManager::RemoveFileFromEffectEngine(const char* aPath)
{
	if (myEffectEngine->getSoundSource(aPath) != nullptr)
	{
		myEffectEngine->removeSoundSource(myEffectEngine->getSoundSource(aPath));
	}
}

void AudioManager::RemoveAllAudioFromEffectEngine()
{
	myEffectEngine->removeAllSoundSources();
}

void AudioManager::SetMusicVolumeMultiplier(float aNewMultiplier)
{
	myMusicMultiplier = aNewMultiplier;
	SetVolume();
}

void AudioManager::SetEffectVolumeMultiplier(float aNewMultiplier)
{
	myEffectsMultiplier = aNewMultiplier;
	SetVolume();
}

void AudioManager::SetSoundVolumeMultiplier(float aNewMultiplier)
{
	mySoundMultiplier = aNewMultiplier;
	SetVolume();
}

const bool AudioManager::IsMusicCurrentlyPlaying(const char* aPath) const
{
	return myMusicEngine->isCurrentlyPlaying(aPath);
}

const bool AudioManager::IsEffectCurrentlyPlaying(const char* aPath) const
{
	return myEffectEngine->isCurrentlyPlaying(aPath);
}

void AudioManager::SetVolume()
{
	myEffectEngine->setSoundVolume(myEffectsMultiplier * mySoundMultiplier);
	myMusicEngine->setSoundVolume(myMusicMultiplier * mySoundMultiplier);
}
