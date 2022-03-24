#include "pch.h"
#include <iostream>
#include "Level.h"

Level::Level(float scale)
	: m_pBackground{new Texture("./Resources/Background.png")}
	, m_TextureHeight{ m_pBackground ->GetHeight()}
	, m_TextureWidth { m_pBackground->GetWidth()}
	, m_Scale{scale}
{
	std::cout << "Level Built" << '\n';
}

Level::~Level()
{
	DeleteTextures();
}

void Level::DrawBackground() const
{
	Rectf destRect{};
	destRect.bottom = 0;
	destRect.left = 0;
	destRect.height = m_TextureHeight * m_Scale ;
	destRect.width = 510;
	m_pBackground->Draw(destRect);
}


void Level::DeleteTextures()
{
	delete m_pBackground;
	m_pBackground = nullptr;
}