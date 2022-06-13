#pragma once
#include "Texture.h"
class HUD
{
public:
	HUD(const Point2f& topLeft, int totalPowerUps);
	~HUD();
	void Draw() const;
	void PowerUpHit();
private:

	void DrawLeftTexture(Point2f& bottomLeft) const;
	void DrawCenterTexture(Point2f& bottomLeft) const;
	void DrawRightTexture(Point2f& bottomLeft) const;

	Point2f m_BottomLeft;
	int m_TotalPowerUps;
	int m_HitPowerUps;
	Texture* m_pLeftTexture;
	Texture* m_pRightTexture;
	Texture* m_pPowerUpTexture;

	Point2f m_PowerUpBottomLeft{};
	Point2f m_RightTextureBottomLeft{};
};

