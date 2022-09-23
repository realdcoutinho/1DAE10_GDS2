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

	Texture* GetTexturePointer(const std::string& name) const;

private:
	void AssignTextures();
	std::unordered_map<std::string, Texture*> m_TextureMap;
};

