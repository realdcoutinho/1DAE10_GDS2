#pragma once
#include "Texture.h"

class TextureManager;
class Player;
class HUD
{
public:
	HUD(TextureManager* textureManagerpointer, Player*  player, const Point2f& topLeft, int numberOfLifes);
	HUD(const HUD& other) = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD(HUD&& other) = delete;
	HUD& operator=(HUD&& other) = delete;

	~HUD();
	void Draw() const;
	void LostLife();
private:
	void DrawTexture(Point2f& bottomLeft) const;
	Rectf GetDestRect(Point2f& bottomLeft) const; 

	TextureManager* m_pTextureManager;
	Player* m_pPlayer;
	Texture* m_pTexture;

	int m_TotalOfLifes;
	int m_HitPowerUps;
	float m_Scale;
	float m_SpaceInterval;
	Point2f m_BottomLeft;
};

