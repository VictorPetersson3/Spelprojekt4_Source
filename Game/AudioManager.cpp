#include "stdafx.h"
#include "AudioManager.h"

AudioManager AudioManager::myInstance;

AudioManager::AudioManager()
{
	myAudioEngine = irrklang::createIrrKlangDevice();
}

AudioManager::~AudioManager()
{
	myAudioEngine->drop();
}

void AudioManager::Play2D(const char* aPath)
{
	myAudioEngine->play2D(aPath);
}

void AudioManager::Play2D(const char* aPath, bool aLooping)
{
	myAudioEngine->play2D(aPath, aLooping);
}

void AudioManager::Play2D(const char* aPath, bool aLooping, float volume)
{
	irrklang::ISoundSource* sound = myAudioEngine->addSoundSourceFromFile(aPath);

	if (sound != nullptr)
	{
		sound->setDefaultVolume(volume);

		myAudioEngine->play2D(sound, aLooping, false, false);

	}
	else
	{
		myAudioEngine->play2D(myAudioEngine->getSoundSource(aPath), aLooping, false, false);
	}
}

void AudioManager::StopAllSounds()
{
	myAudioEngine->stopAllSounds();
}

void AudioManager::StopSound(const char* aPath)
{
	if (myAudioEngine->getSoundSource(aPath) != nullptr)
	{
		myAudioEngine->stopAllSoundsOfSoundSource(myAudioEngine->getSoundSource(aPath));
	}
}

void AudioManager::RemoveFileFromEngine(const char* aPath)
{
	if (myAudioEngine->getSoundSource(aPath) != nullptr)
	{
		myAudioEngine->removeSoundSource(myAudioEngine->getSoundSource(aPath));
	}
}

void AudioManager::RemoveAllAudioFromEngine()
{
	myAudioEngine->removeAllSoundSources();
}

void AudioManager::SetVolumeMultiplier(float aNewMultiplier)
{
	volumeMultiplier = aNewMultiplier;

	myAudioEngine->setSoundVolume(volumeMultiplier);
}

bool AudioManager::IsCurrentlyPlaying(const char* aPath)
{
	return myAudioEngine->isCurrentlyPlaying(aPath);
}
