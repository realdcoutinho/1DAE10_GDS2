#pragma once
#include "utils.h"
class Enemy
{
public:
	Enemy();
	Enemy(Point2f center, float width, float height);
	~Enemy();

	void Draw();
	bool DoHitTest(const Rectf& rect);
	bool DoHitTest(const Point2f& pos);
	//void SetCenter(const Point2f& center);
	//void SetDimensions(float width, float height);
	//bool IsDead();

	//mine
	float GetWidth() const;
	float GetHeight() const;

private:
	Point2f m_Center;
	float m_Width;
	float m_Height;
	bool m_IsDead{false};

	//mine
	Color4f m_EnemyColor{ 1, 0, 0, 1 };
	Rectf m_Enemy;
	//static int m_NrOfInstances;
};

