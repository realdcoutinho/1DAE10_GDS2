#include "pch.h"
#include "Platform.h"
#include <iostream>
using namespace utils;

Platform::Platform(const Point2f& bottomLeft)
	: m_Shape{0, 0, 0, 0}
	, m_pTexture{new Texture{"./resources/Images/platform.png"}}
	, m_Location{ bottomLeft }

{
	SetVertices();
	std::cout << "Platform created" << '\n';
}

Platform::~Platform()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Platform::Draw() const
{
	m_pTexture->Draw(m_Location);
}

bool Platform::IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity)
{
	Point2f actorBottomCenter{ actorShape.left + actorShape.width / 2, actorShape.bottom };
	Point2f actorTopCenter{ actorShape.left + actorShape.width / 2, actorShape.height };

	HitInfo hitInfo{};
	if (actorVelocity.y > 0)
	{
		return false;
	}
	else if (Raycast(m_Vertices, actorBottomCenter, actorTopCenter, hitInfo))
	{
			return true;
	}
	else 
	{
		return false;
	}
}

void Platform::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	Point2f actorBottomCenter{ actorShape.left + actorShape.width / 2, actorShape.bottom - 1 };
	Point2f actorTopCenter{ actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height };

	HitInfo hitInfo{};
	if (Raycast(m_Vertices, actorBottomCenter, actorTopCenter, hitInfo) && actorVelocity.y < 0)
	{
		actorVelocity.y = 0;
		actorShape.bottom = hitInfo.intersectPoint.y;
	}
}


void Platform::SetVertices()
{
	Point2f point2{ m_Location.x + m_pTexture->GetWidth(), m_Location.y };
	Point2f point3{ m_Location.x, m_Location.y + m_pTexture->GetHeight() };
	Point2f point4{ m_Location.x + m_pTexture->GetWidth() ,  m_Location.y + m_pTexture->GetHeight() };
	m_Vertices.push_back(m_Location);
	m_Vertices.push_back(point2);
	m_Vertices.push_back(point3);
	m_Vertices.push_back(point4);
}