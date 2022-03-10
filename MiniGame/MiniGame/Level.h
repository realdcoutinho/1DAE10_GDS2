#pragma once
#include "utils.h"
#include "Texture.h"
#include <vector>

class Level
{
public:
	Level();
	~Level();
	void DrawBackground();
	void DrawForeground();
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	bool IsOnGround( const Rectf& actorShape);
private:
	std::vector<Point2f> m_Vertices;
	Texture* m_pBackgroundTexture;
	Texture* m_pForegroundTexture;
	Point2f m_FenceBottomLeft;

	void AddVertices();
	bool CheckRaycast(const Rectf& actorShape, utils::HitInfo& hitInfo);
};

