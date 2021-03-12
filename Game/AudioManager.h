#pragma once
#include "irrKlang\irrKlang.h"

class AudioManager
{
public:
	AudioManager(const AudioManager&) = delete;

	static AudioManager& GetInstance()
	{
		return myInstance;
	}

	irrklang::ISoundEngine* myAudioEngine;

	void Play2D(const char* aPath);
	void Play2D(const char* aPath, bool aLooping);
	void Play2D(const char* aPath, bool aLooping, float volume);

	void StopAllSounds();
	void StopSound(const char* aPath);

	void RemoveFileFromEngine(const char* aPath);
	void RemoveAllAudioFromEngine();

	void SetVolumeMultiplier(float aNewMultiplier);

	bool IsCurrentlyPlaying(const char* aPath);

private:
	float volumeMultiplier = 1;

	AudioManager();
	~AudioManager();

	static AudioManager myInstance;
};



