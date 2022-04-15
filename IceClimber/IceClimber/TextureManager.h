#pragma once
#include <unordered_map>
#include "Texture.h"
#include "utils.h"
class TextureManager final
{
public:
	explicit TextureManager();
	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator=(const TextureManager& other) = delete;
	TextureManager(TextureManager&& other) = delete;
	TextureManager& operator=(TextureManager&& other) = delete;
	~TextureManager();

	Texture* GetTexturePointer(const std::string& name);
	float GetTextureWidth(const std::string& name) ;
	float GetTextureHeight(const std::string& name) ;

private:
	void AssignTextures();
	std::unordered_map<std::string, Texture*> m_TextureMap;

	Texture* m_pBackground;
	Texture* m_pForeGround;

	Texture* m_pSeal;
	Texture* m_pBear;
	Texture* m_pBird;

	Texture* m_pEnemyAlive;
	Texture* m_pEnemyDead;
	Texture* m_pStalagmites; //doest work
	Texture* m_pWinningBird;
	Texture* m_pBlocks;
	Texture* m_pBonus;

};

