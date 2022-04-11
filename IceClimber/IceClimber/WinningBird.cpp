#include "pch.h"
#include "WinningBird.h"
#include <iostream>
using namespace utils;

WinningBird::WinningBird(Point2f bottomLeft, int type)
	: NPC(bottomLeft)
	, m_Type{ColorBird(type)}
	, m_NrRows{2}
	, m_NrColumns{4}
{
	std::cout << "Winning Bird Created" << '\n';
	SetMeasures();
}

WinningBird::~WinningBird()
{
	delete m_pTextureBird;
}

void WinningBird::Draw() const
{
	Rectf sourceRect{ m_SourceRect };
	m_pTextureBird->Draw(m_BottomLeft, sourceRect);
}

void WinningBird::SetMeasures()
{
	m_TextureWidth = m_pTextureBird->GetWidth();
	m_TextureHeight = m_pTextureBird->GetHeight();
	m_TextureWidthSnipet = m_TextureWidth / m_NrColumns;
	m_TextureHeightSnipet = m_TextureHeight / m_NrRows;
}