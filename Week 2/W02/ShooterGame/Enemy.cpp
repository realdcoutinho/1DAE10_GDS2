#include "pch.h"
#include "Enemy.h"
#include <iostream>
using namespace utils;

//static int m_NrOfInstances{};

Enemy::Enemy()
{

}

Enemy::Enemy(Point2f center, float width, float height)
	: m_Center{ center }
	, m_Width{width}
	, m_Height{height}
{
	Rectf enemy{ m_Center.x - m_Width / 2, m_Center.y - m_Height / 2, m_Width, m_Height };
	m_Enemy = enemy;
	//++m_NrOfInstances;
	//std::cout << "Enemy number: " << m_NrOfInstances << " was created" << '\n';
}

Enemy::~Enemy()
{
	//std::cout << "Enemy number: " << m_NrOfInstances << " was destryoed" << '\n';
	//--m_NrOfInstances;
}

void Enemy::Draw()
{
	if (m_IsDead)
	{

	}
	else
	{
		SetColor(m_EnemyColor);
		DrawRect(m_Enemy, 2);
	}
}

bool Enemy::DoHitTest(const Rectf& rect)
{
	return IsOverlapping(rect, m_Enemy);
}

bool Enemy::DoHitTest(const Point2f& pos)
{
	Color4f newColor{ 0, 1, 0, 1 };

	bool hit{ IsPointInRect(pos, m_Enemy) };
	if (hit)
	{
		m_EnemyColor = newColor;
		std::cout << "It was hit" << '\n';
		m_IsDead = true;
		return hit;
	}
	else
	{
		return false;
	}
}


//bool Enemy::IsDead()
//{
//	
//}

float Enemy::GetWidth() const
{
	return m_Width;
}

float Enemy::GetHeight() const
{
	return m_Height;
}
