#pragma once
#include "utils.h"
#include "Texture.h"
#include <vector>

class Level
{
public:
	Level();
	void DrawBackground();
	void DrawForegroud();
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	bool IsOnGround(const Rectf& actorShape);
private:
	std::vector<Point2f> m_Vertices;
	Texture* m_pBackgroundTexture;
	Texture* m_pFenceTexture;
	Point2f m_FenceBottomLeft;
};

