#pragma once
#include "Texture.h"
#include "utils.h"

class Platform
{
public:
	Platform(const Point2f& bottomLeft);
	void Draw() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	bool IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity);
private:
	Rectf m_Shape;
	Texture* m_pTexture;
};

