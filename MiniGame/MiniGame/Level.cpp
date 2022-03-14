#include "pch.h"
#include "Level.h"
#include <iostream>
using namespace utils;


Level::Level() 
	: m_pBackgroundTexture{new Texture{"./resources/Images/background.png" }}
	, m_pForegroundTexture{ new Texture{"./resources/Images/fence.png" } }
{
	AddVertices();
}

Level::~Level()
{
	delete m_pBackgroundTexture;
	delete m_pForegroundTexture;
	m_pBackgroundTexture = nullptr;
	m_pForegroundTexture = nullptr;
}


void Level::DrawBackground() const
{
	m_pBackgroundTexture->Draw();
	SetColor(Color4f{ 0.0f, 0.0f, 1.0f, 1.0f });
	DrawPolygon(m_Vertices);
}

void Level::DrawForeground() const
{
	Point2f fencePos{ 200, 190 };
	m_pForegroundTexture->Draw(fencePos);
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const 
{
	Point2f actorBottomCenter{ actorShape.left + actorShape.width / 2, actorShape.bottom - 1 };
	Point2f actorTopCenter{ actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height };

	HitInfo hitInfo{};
	if (Raycast(m_Vertices, actorBottomCenter, actorTopCenter, hitInfo))
	{
		actorVelocity.y = 0;
		actorShape.bottom = hitInfo.intersectPoint.y;
	}
}

bool Level::IsOnGround(const Rectf& actorShape) const
{
	
	Point2f actorBottomCenter{ actorShape.left + actorShape.width / 2, actorShape.bottom - 1 };
	Point2f actorTopCenter{ actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height };

	HitInfo hitInfo{};
	return (Raycast(m_Vertices, actorBottomCenter, actorTopCenter, hitInfo));
}

void Level::AddVertices()
{
	m_Vertices.push_back(Point2f{ 0.0f, 0.0f });
	m_Vertices.push_back(Point2f{ 0.0f, 190.0f });
	m_Vertices.push_back(Point2f{ 340.0f, 190.0f });
	m_Vertices.push_back(Point2f{ 408.0f, 124.0f });
	m_Vertices.push_back(Point2f{ 560.0f, 124.0f });
	m_Vertices.push_back(Point2f{ 660.0f, 224.0f });
	m_Vertices.push_back(Point2f{ 846.0f, 224.0f });
	m_Vertices.push_back(Point2f{ 846.0f, 0.0f });
	m_Vertices.push_back(Point2f{ 0.0f, 0.0f });
}
