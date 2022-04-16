#include "pch.h"
#include "TextureManager.h"
#include <iostream>
using namespace utils;

TextureManager::TextureManager()
{
	std::cout << "Texture Manager" << '\n';
	AssignTextures();
}

TextureManager::~TextureManager()
{
	//delete m_pBackground;
	//delete m_pForeGround;

	//delete m_pSeal;
	//delete m_pBear;
	//delete m_pBird;

	//delete m_pEnemyAlive;
	//delete m_pEnemyDead;

	//delete m_pStalagmites;
	//delete m_pWinningBird;
	//delete m_pBlocks;
	//delete m_pBonus;

	//size_t size{ m_TextureMap.size() };

	//for (int i{}; i < size; ++i)
	//{
	//	std::string j = std::to_string(i);
	//	delete m_TextureMap[j].second;
	//}

	std::unordered_map<std::string, Texture*>::iterator curentTexture = m_TextureMap.begin();

	while (curentTexture != m_TextureMap.end())
	{
		delete curentTexture->second;
		++curentTexture;
	}



}

void TextureManager::AssignTextures()
{
	m_TextureMap["Background"]  = new Texture("./Images/Background.png");
	m_TextureMap["Foreground"]  = new Texture("./Images/Foreground.png");
	m_TextureMap["EnemyAlive"]	= new Texture("./Images/EnemiesAlive.png");
	m_TextureMap["EnemyDead"]	= new Texture("./Images/EnemiesDead.png");
	m_TextureMap["Stalagmite"]  = new Texture("./Images/Stalagmite.png");
	m_TextureMap["WinningBird"] = new Texture("./Images/WinningBird.png");
	m_TextureMap["Block"]		= new Texture("./Images/IC_Blocks.png");
	m_TextureMap["Bonus"]		= new Texture("./Images/BonusVegetables.png");
	m_TextureMap["Seal"]		= new Texture("./Images/SealEnemy.png");
	m_TextureMap["Bear"]		= new Texture("./Images/BearEnemy.png");
	m_TextureMap["Bird"]		= new Texture("./Images/BirdEnemy.png");
}

Texture* TextureManager::GetTexturePointer(const std::string& name)
{
	if (m_TextureMap.contains(name))
		return m_TextureMap[name];
	else
		return nullptr;
}

float TextureManager::GetTextureWidth(const std::string& name)
{
	float width{ m_TextureMap[name]->GetWidth() };
	return width;
}
float TextureManager::GetTextureHeight(const std::string& name) 
{
	float height{ m_TextureMap[name]->GetHeight() };
	return height;
}