#include "pch.h"
#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
	: m_CurrentVolume	{7}
	, m_MaxVolume		{15}
	, m_MinVolume		{0}
	, m_VolumeState     {Volume::volumeOn}
	, m_MusicState		{MusicState::musicOn}
{
	AssignSoundStreams();
	AssignSoundEffects();
	SetVolume();
}

SoundManager::~SoundManager()
{
	std::unordered_map<std::string, SoundStream*>::iterator currentSoundStream = m_SoundStreamMap.begin();
	while (currentSoundStream != m_SoundStreamMap.end())
	{
		delete currentSoundStream->second;
		++currentSoundStream;
	}

	std::unordered_map<std::string, SoundEffect*>::iterator currentSoundEffect = m_SoundEffectMap.begin();
	while (currentSoundEffect != m_SoundEffectMap.end())
	{
		delete currentSoundEffect->second;
		++currentSoundEffect;
	}
}

void SoundManager::AssignSoundStreams()
{
	m_SoundStreamMap["GameMusic"] = new SoundStream("./Sounds/SoundStreamMusic.mp3");
}

void SoundManager::AssignSoundEffects()
{
	m_SoundEffectMap["Jump"] = new SoundEffect("./Sounds/Sound Effect_Jumping.wav");
	//m_SoundEffectMap["Dead"] = new SoundEffect("./Sound/Player_v5.png");
	m_SoundEffectMap["EnemyDead"] = new SoundEffect("./Sounds/Sound Effect_Enemy.wav");
	m_SoundEffectMap["Destroyed"] = new SoundEffect("./Sounds/Sound Effect _BlockDestroyed.mp3");
	m_SoundEffectMap["Falling_Stalagtite"] = new SoundEffect("./Sounds/Sound Effect _Falling_Stalagtite.wav");
	m_SoundEffectMap["Block_Fixed"] = new SoundEffect("./Sounds/Sound Effect _Block_Fixed.wav");
	m_SoundEffectMap["PickUp"] = new SoundEffect("./Sounds/Sound Effect_PickUp.wav");
	m_SoundEffectMap["Winning"] = new SoundEffect("./Sounds/Sound Effect_Winning.wav");
}

void SoundManager::DescreaseVolume(int value)
{
	if (m_CurrentVolume > m_MinVolume)
	{
		m_CurrentVolume += value;
		std::unordered_map<std::string, SoundEffect*>::iterator currentSoundEffect = m_SoundEffectMap.begin();
		while (currentSoundEffect != m_SoundEffectMap.end())
		{
			currentSoundEffect->second->SetVolume(m_CurrentVolume);
			++currentSoundEffect;
		}
		std::unordered_map<std::string, SoundStream*>::iterator currentSoundStream = m_SoundStreamMap.begin();

		while (currentSoundStream != m_SoundStreamMap.end())
		{
			currentSoundStream->second->SetVolume(m_CurrentVolume);
			++currentSoundStream;
		}
	}
	PrintCurrent();
}

void SoundManager::IncreaseVolume(int value)
{
	if (m_CurrentVolume < m_MaxVolume)
	{
		m_CurrentVolume += value;
		std::unordered_map<std::string, SoundEffect*>::iterator currentSoundEffect = m_SoundEffectMap.begin();
		while (currentSoundEffect != m_SoundEffectMap.end())
		{
			currentSoundEffect->second->SetVolume(m_CurrentVolume);
			++currentSoundEffect;
		}
		std::unordered_map<std::string, SoundStream*>::iterator currentSoundStream = m_SoundStreamMap.begin();
		while (currentSoundStream != m_SoundStreamMap.end())
		{
			currentSoundStream->second->SetVolume(m_CurrentVolume);
			++currentSoundStream;
		}
	}
	PrintCurrent();
}

void SoundManager::UpdateStates()
{
	std::unordered_map<std::string, SoundStream*>::iterator currentSoundStream = m_SoundStreamMap.begin();
	std::unordered_map<std::string, SoundEffect*>::iterator currentSoundEffect = m_SoundEffectMap.begin();

	switch (m_VolumeState)
	{
	case(Volume::volumeOn):
		while (currentSoundStream != m_SoundStreamMap.end())
		{
			currentSoundStream->second->SetVolume(m_CurrentVolume);
			++currentSoundStream;
		}
		while (currentSoundEffect != m_SoundEffectMap.end())
		{
			currentSoundEffect->second->SetVolume(m_CurrentVolume);
			++currentSoundEffect;
		}
		currentSoundStream = m_SoundStreamMap.begin();
		currentSoundEffect = m_SoundEffectMap.begin();
		break;
	case(Volume::volumeOff):
		while (currentSoundStream != m_SoundStreamMap.end())
		{
			currentSoundStream->second->SetVolume(0);
			++currentSoundStream;
		}
		while (currentSoundEffect != m_SoundEffectMap.end())
		{
			currentSoundEffect->second->SetVolume(0);
			++currentSoundEffect;
		}
		currentSoundStream = m_SoundStreamMap.begin();
		currentSoundEffect = m_SoundEffectMap.begin();
		break;
	}

	switch (m_MusicState)
	{
	case(MusicState::musicOn):
		while (currentSoundStream != m_SoundStreamMap.end())
		{
			currentSoundStream->second->SetVolume(m_CurrentVolume);
			++currentSoundStream;
		}
		currentSoundStream = m_SoundStreamMap.begin();
		break;
	case(MusicState::musicOff):
		while (currentSoundStream != m_SoundStreamMap.end())
		{
			currentSoundStream->second->SetVolume(0);
			++currentSoundStream;
		}
		currentSoundStream = m_SoundStreamMap.begin();
		break;
	}
}

void SoundManager::ChangeAllSounds()
{
	switch (m_VolumeState)
	{
	case(Volume::volumeOn):
		m_VolumeState = Volume::volumeOff;
		break;
	case(Volume::volumeOff):
		m_VolumeState = Volume::volumeOn;
		break;
	}
}

void SoundManager::ChangeMusic()
{
	switch (m_MusicState)
	{
	case(MusicState::musicOn):
		m_MusicState = MusicState::musicOff;
		break;
	case(MusicState::musicOff):
		m_MusicState = MusicState::musicOn;
		break;
	}
}

SoundStream* SoundManager::GetSoundStreamPointer(const std::string& name) const
{
	if (m_SoundStreamMap.contains(name))
		return m_SoundStreamMap.at(name);
	else
		return nullptr;
}

SoundEffect* SoundManager::GetSoundEffectPointer(const std::string& name) const
{
	if (m_SoundEffectMap.contains(name))
		return m_SoundEffectMap.at(name);
	else
		return nullptr;
}

void SoundManager::SetVolume()
{
	std::unordered_map<std::string, SoundEffect*>::iterator currentSoundEffect = m_SoundEffectMap.begin();
	while (currentSoundEffect != m_SoundEffectMap.end())
	{
		currentSoundEffect->second->SetVolume(m_CurrentVolume);
		++currentSoundEffect;
	}
	std::unordered_map<std::string, SoundStream*>::iterator currentSoundStream = m_SoundStreamMap.begin();
	while (currentSoundStream != m_SoundStreamMap.end())
	{
		currentSoundStream->second->SetVolume(m_CurrentVolume);
		++currentSoundStream;
	}
}

void SoundManager::PrintVolume() const
{
	std::cout << "Volume Values:  " << '\n';
	std::cout << "Max: " << m_MaxVolume << '\n';
	std::cout << "Min: " << m_MinVolume << '\n';
	std::cout << "Current: " << m_CurrentVolume << '\n';
	std::cout << '\n' << '\n';
}

void SoundManager::PrintCurrent() const
{
	std::cout << "Current Volume:" << m_CurrentVolume << '\n';
}