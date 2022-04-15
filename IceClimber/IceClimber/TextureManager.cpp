#include "pch.h"
#include "TextureManager.h"
#include <iostream>
using namespace utils;

TextureManager::TextureManager()
	: m_pBackground	{ new Texture("./Images/Background.png") }
	, m_pForeGround	{ new Texture("./Images/Foreground.png") }
	, m_pEnemyAlive	{ new Texture("./Images/EnemiesAlive.png") }
	, m_pEnemyDead	{ new Texture("./Images/EnemiesDead.png") }
	, m_pStalagmites{ new Texture("./Images/Stalagmite.png") }
	, m_pWinningBird{ new Texture("./Images/WinningBird.png") }
	, m_pBlocks		{ new Texture("./Images/IC_Blocks.png")}
	, m_pBonus		{ new Texture("./Images/BonusVegetables.png") }
	, m_pSeal		{ new Texture("./Images/SealEnemy.png") }
	, m_pBear		{ new Texture("./Images/BearEnemy.png") }
	, m_pBird		{ new Texture("./Images/BirdEnemy.png") }
{
	std::cout << "Texture Manager" << '\n';
	AssignTextures();
}

TextureManager::~TextureManager()
{
	delete m_pBackground;
	delete m_pForeGround;

	delete m_pSeal;
	delete m_pBear;
	delete m_pBird;

	delete m_pEnemyAlive;
	delete m_pEnemyDead;

	delete m_pStalagmites;
	delete m_pWinningBird;
	delete m_pBlocks;
	delete m_pBonus;
}

void TextureManager::AssignTextures()
{
	m_TextureMap["Background"]  = m_pBackground;
	m_TextureMap["Foreground"]  = m_pForeGround;
	m_TextureMap["EnemyAlive"]	= m_pEnemyAlive;
	m_TextureMap["EnemyDead"]	= m_pEnemyDead;
	m_TextureMap["Stalagmite"]  = m_pStalagmites;
	m_TextureMap["WinningBird"] = m_pWinningBird;
	m_TextureMap["Block"]		= m_pBlocks;
	m_TextureMap["Bonus"]		= m_pBonus;
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