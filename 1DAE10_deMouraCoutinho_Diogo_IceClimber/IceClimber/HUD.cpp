#include "pch.h"
#include "HUD.h"
#include <iostream>
#include "TextureManager.h"
#include "Player.h"

HUD::HUD(TextureManager* textureManagerpointer, Player* player, const Point2f& topLeft, int numberOfLifes)
	: m_pTextureManager{ textureManagerpointer }
	, m_pPlayer{ player }
	, m_BottomLeft{ topLeft }
	, m_TotalOfLifes{ numberOfLifes }
	, m_HitPowerUps{0}
	, m_pTexture{ m_pTextureManager ->GetTexturePointer("Life_HUD")}
	, m_Scale{4}
	, m_SpaceInterval{10}
{
}

HUD::~HUD()
{
}

void HUD::LostLife()
{
	if (m_pPlayer->IsPlayerHit())
		--m_TotalOfLifes;
}

void HUD::Draw() const
{
	if (m_TotalOfLifes <= 0)
	{

	}
	else 
	{
		Point2f hudOrigin{ m_BottomLeft };
		DrawTexture(hudOrigin);
	}
}

void HUD::DrawTexture(Point2f& bottomLeft) const
{
	const float hudCenterWidth{ m_pTexture->GetWidth() };
	const float hudCenterHeight{ m_pTexture->GetHeight() };
	Rectf sourceRect{ 0.0f, 0.0f, hudCenterWidth, hudCenterHeight};

	for (int i{ 0 }; i < m_TotalOfLifes; ++i)
	{
		sourceRect.left = (i < m_HitPowerUps) ? 0.0f : hudCenterWidth;
		m_pTexture->Draw(GetDestRect(bottomLeft));
		bottomLeft.x += m_pTexture->GetWidth() * m_Scale + m_SpaceInterval;
	}
}

Rectf HUD::GetDestRect(Point2f& bottomLeft) const
{
	return Rectf{ bottomLeft.x, bottomLeft.y, m_pTexture->GetWidth() * m_Scale, m_pTexture->GetHeight() * m_Scale };
}

