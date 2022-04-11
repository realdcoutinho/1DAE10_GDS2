#pragma once
#include "Texture.h"
#include "utils.h"

class Platform
{
public:
	Platform(const Point2f& bottomLeft);
	~Platform();
	void Draw() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	bool IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity);
	void SetVertices();
private:
	std::vector<Point2f> m_Vertices{};
	Rectf m_Shape;
	Texture* m_pTexture;
	Point2f m_Location;
};

