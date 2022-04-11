#pragma once
#include "Vector2f.h"
#include "utils.h"
#include "Texture.h"
#include "Platform.h"
#include <vector>

class Level
{
public:
	Level();
	~Level();
	void DrawBackground() const;
	void DrawForeground() const;
	void DrawEnd() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround( const Rectf& actorShape, Vector2f& actorVelocity) const;
	bool HasReachedEnd(const Rectf& actorshape);
	Rectf GetBoundaries() const;
	
	bool m_EndReched;
private:
	Platform* m_pPlatform;
	std::vector<Point2f> m_Vertices;
	Texture* m_pBackgroundTexture;
	Texture* m_pForegroundTexture;

	Texture* m_pEndSignTexture;
	Rectf m_EndSignShape;
	
	Point2f m_EndLocation;
	
	Point2f m_FenceBottomLeft;
	Rectf m_Boundaries;

	void AddVertices();

};
