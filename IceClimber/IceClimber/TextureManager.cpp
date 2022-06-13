#include "pch.h"
#include "TextureManager.h"
#include <iostream>
using namespace utils;

TextureManager::TextureManager()
{
	AssignTextures();
}

TextureManager::~TextureManager()
{	
	std::unordered_map<std::string, Texture*>::iterator curentTexture = m_TextureMap.begin();
	while (curentTexture != m_TextureMap.end())
	{
		delete curentTexture->second;
		++curentTexture;
	}
}

void TextureManager::AssignTextures()
{
	m_TextureMap["Player"]		= new Texture("./Images/Player_v5.png");
	m_TextureMap["Background"]  = new Texture("./Images/Background.png");
	m_TextureMap["Foreground"]  = new Texture("./Images/Foreground.png");
	m_TextureMap["EnemyAlive"]	= new Texture("./Images/EnemiesAlive.png");
	m_TextureMap["EnemyDead"]	= new Texture("./Images/EnemiesDead.png");
	m_TextureMap["WinningBird"] = new Texture("./Images/WinningBird.png");
	m_TextureMap["Cloud"]		= new Texture("./Images/Clouds.png");
	m_TextureMap["Block"]		= new Texture("./Images/IC_Blocks.png");
	m_TextureMap["Bonus"]		= new Texture("./Images/BonusVegetables.png");
	m_TextureMap["Stalagmite"]	= new Texture("./Images/Stalagmite.png");
	m_TextureMap["Stalagtites"]	= new Texture("./Images/Stalagtite.png");
}

Texture* TextureManager::GetTexturePointer(const std::string& name) const
{
	if (m_TextureMap.contains(name))
		return m_TextureMap.at(name);
	else
		return nullptr;
}