#pragma once
#include "Vector2f.h"
#include "utils.h"
#include "Texture.h"
#include <vector>

class Level
{
public:
	Level();
	~Level();
	void DrawBackground() const;
	void DrawForeground() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround( const Rectf& actorShape) const;
	Rectf GetBoundaries() const;

private:
	std::vector<Point2f> m_Vertices;
	Texture* m_pBackgroundTexture;
	Texture* m_pForegroundTexture;
	Point2f m_FenceBottomLeft;
	const Rectf m_Boundaries;

	void AddVertices();
};
