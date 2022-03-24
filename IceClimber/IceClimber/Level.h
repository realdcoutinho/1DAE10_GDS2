#pragma once
#include "Texture.h"
class Level
{
public:
	Level(float scale);
	~Level();

	void DrawBackground() const;
private:
	Texture* m_pBackground;
	
	float m_TextureHeight;
	float m_TextureWidth;
	float m_Scale;
	void DeleteTextures();
};

