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


	void PlayMusic(const char* aPath);
	void PlayMusic(const char* aPath, bool aLooping);
	void PlayMusic(const char* aPath, bool aLooping, float volume);

	void PlayEffect(const char* aPath);
	void PlayEffect(const char* aPath, bool aLooping);
	void PlayEffect(const char* aPath, bool aLooping, float volume);

	void StopAllMusic();
	void StopAllEffects();
	void StopMusicSound(const char* aPath);
	void StopEffectSound(const char* aPath);

	void RemoveFileFromMusicEngine(const char* aPath);
	void RemoveAllAudioFromMusicEngine();

	void RemoveFileFromEffectEngine(const char* aPath);
	void RemoveAllAudioFromEffectEngine();

	void SetMusicVolumeMultiplier(float aNewMultiplier);
	void SetEffectVolumeMultiplier(float aNewMultiplier);

	const bool IsMusicCurrentlyPlaying(const char* aPath) const;
	const bool IsEffectCurrentlyPlaying(const char* aPath) const;

private:
	float myMusicMultiplier = 1;
	float myEffectsMultiplier = 1;

	irrklang::ISoundEngine* myMusicEngine;
	irrklang::ISoundEngine* myEffectEngine;
	AudioManager();
	~AudioManager();

	static AudioManager myInstance;
};



