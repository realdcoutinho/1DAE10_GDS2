#pragma once
#include <unordered_map>
#include "Texture.h"
#include "SoundStream.h"
#include "SoundEffect.h"
#include "utils.h"
class SoundManager
{
public:
	explicit SoundManager();
	SoundManager(const SoundManager& other) = delete;
	SoundManager& operator=(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) = delete;
	SoundManager& operator=(SoundManager&& other) = delete;
	~SoundManager();

	void DescreaseVolume(int value);
	void IncreaseVolume(int value);
	void UpdateStates();

	void ChangeAllSounds();
	void ChangeMusic();

	void PrintVolume() const;
	void PrintCurrent() const;



	SoundStream* GetSoundStreamPointer(const std::string& name) const;
	SoundEffect* GetSoundEffectPointer(const std::string& name) const;

private:
	void AssignSoundStreams();
	void AssignSoundEffects();
	void SetVolume();

	enum class MusicState
	{
		musicOn = 0,
		musicOff = 1,
	};
	MusicState m_MusicState;

	enum class Volume
	{
		volumeOn = 0,
		volumeOff = 1,
	};
	Volume m_VolumeState;

	int m_SoundValue;
	int m_CurrentVolume;
	int m_MaxVolume;
	int m_MinVolume;

	std::unordered_map<std::string, SoundStream*> m_SoundStreamMap;
	std::unordered_map<std::string, SoundEffect*> m_SoundEffectMap;
};