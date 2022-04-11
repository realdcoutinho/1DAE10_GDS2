#include "pch.h"
#include "HUD.h"
#include <iostream>

HUD::HUD(const Point2f& topLeft, int totalPowerUps)
	: m_BottomLeft{ topLeft }
	, m_TotalPowerUps{ totalPowerUps}
	, m_HitPowerUps{0}
	, m_pLeftTexture{new Texture{"./resources/Images/HudLeft.png"}}
	, m_pRightTexture{new Texture{"./resources/Images/HudRight.png"}}
	, m_pPowerUpTexture{new Texture{"./resources/Images/HudPowerUp.png"}}
{
	std::cout << " HUD Constructor " << '\n';

	m_PowerUpBottomLeft = Point2f{ m_BottomLeft.x + m_pLeftTexture->GetWidth(), m_BottomLeft.y };
	m_RightTextureBottomLeft = Point2f{ m_PowerUpBottomLeft.x + m_pPowerUpTexture->GetWidth(), m_BottomLeft.y };
}

HUD::~HUD()
{
	delete m_pLeftTexture;
	delete m_pRightTexture;
	delete m_pPowerUpTexture;
}

void HUD::PowerUpHit()
{
	++m_HitPowerUps;
}

void HUD::Draw() const
{
	Point2f hudOrigin{ m_BottomLeft };
	DrawLeftTexture(hudOrigin);
	DrawCenterTexture(hudOrigin);
	DrawRightTexture(hudOrigin);
}

void HUD::DrawLeftTexture(Point2f& bottomLeft) const
{
	m_pLeftTexture->Draw(bottomLeft);
	bottomLeft.x += m_pLeftTexture->GetWidth();
}

void HUD::DrawCenterTexture(Point2f& bottomLeft) const
{
	const float hudCenterWidth{ m_pPowerUpTexture->GetWidth() / 2 };
	const float hudCenterHeight{ m_pPowerUpTexture->GetHeight() };
	Rectf sourceRect{ 0.0f, 0.0f, hudCenterWidth, hudCenterHeight };

	for (int i{ 0 }; i < m_TotalPowerUps; ++i)
	{
		sourceRect.left = (i < m_HitPowerUps) ? 0.0f : hudCenterWidth;
		m_pPowerUpTexture->Draw(bottomLeft, sourceRect);
		bottomLeft.x += hudCenterWidth;
	}

}

void HUD::DrawRightTexture(Point2f& bottomLeft) const
{
	m_pRightTexture->Draw(bottomLeft);
}