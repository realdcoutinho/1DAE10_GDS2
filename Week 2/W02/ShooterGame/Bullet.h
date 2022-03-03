#pragma once
#include "utils.h"
class Enemy;

class Bullet
{
public:
	Bullet();
	Bullet(float width, float height);
	void Draw();
	void Update(float elapsedSec, Enemy** pEnemies, int numEnemies);
	void Shoot(const Point2f center, const Vector2f velocity);
	void SetDimensions(float width, float height);
	void SetBoundaries(const Rectf& boundaries);


private:
	void CheckBoundaries();

	Point2f m_Center;
	float m_Width;
	float m_Height;
	Vector2f m_Velocity;
	Rectf m_Boundaries;
	bool m_IsActivated;

};

