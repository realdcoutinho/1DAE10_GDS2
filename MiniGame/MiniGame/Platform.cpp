#include "pch.h"
#include "Platform.h"
#include <iostream>
using namespace utils;

Platform::Platform(const Point2f& bottomLeft)
	: m_Shape{0, 0, 0, 0}
	, m_pTexture{new Texture{"./resources/Images/platform.png"}}
{
	std::cout << "Platform created" << '\n';
}

void Platform::Draw() const
{
	m_pTexture->Draw();
}

bool IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity)
{
	Point2f actorBottomCenter{ actorShape.left + actorShape.width / 2, actorShape.bottom };
	Point2f actorTopCenter{ actorShape.left + actorShape.width / 2, actorShape.height };

	std::vector<Point2f> m_Vertices;
	if (actorVelocity.y > 0)
	{
		HitInfo hitInfo{};
		if (Raycast(m_Vertices, actorBottomCenter, actorTopCenter, hitInfo))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else 
	{
		return false;
	}
}