#include "pch.h"
#include "Level.h"
#include "SVGParser.h"
#include <iostream>
using namespace utils;


Level::Level() 
	: m_pBackgroundTexture{new Texture{"./resources/Images/background.png" }}
	, m_pForegroundTexture{ new Texture{"./resources/Images/fence.png" } }
	, m_pEndSignTexture{new Texture{"./resources/Images/EndSign.png" }}
	, m_Boundaries{}
	, m_FenceBottomLeft{ 200.0f, 190.0f }
	, m_pPlatform{ new Platform(Point2f{260.0f, 320.0f}) }
	, m_EndReched{ false }
	, m_EndLocation{ 730.0f, 224.0f }

{
	m_Boundaries = Rectf{ 0.0f, 0.0f, m_pBackgroundTexture->GetWidth(), m_pBackgroundTexture->GetHeight() };
	std::vector<std::vector<Point2f>> svgVertices{};
	if (SVGParser::GetVerticesFromSvgFile("./resources/Images/level.svg", svgVertices))
	{
		m_Vertices = svgVertices[0];
		//std::cout << "It worked" << '\n';
	}
	else
	{
		std::cout << "Level failed to load from svg" << std::endl;
		AddVertices();
	}


	m_EndSignShape.left = m_EndLocation.x;
	m_EndSignShape.bottom = m_EndLocation.y;
	m_EndSignShape.width = m_pEndSignTexture->GetWidth();
	m_EndSignShape.height = m_pEndSignTexture->GetHeight();

}

Level::~Level()
{
	delete m_pBackgroundTexture;
	delete m_pForegroundTexture;
	delete m_pEndSignTexture;
	m_pEndSignTexture = nullptr;
	m_pBackgroundTexture = nullptr;
	m_pForegroundTexture = nullptr;
	delete m_pPlatform;
	m_pPlatform = nullptr;
}


void Level::DrawBackground() const
{
	m_pBackgroundTexture->Draw();
	m_pEndSignTexture->Draw(m_EndLocation);
	m_pPlatform->Draw();

	SetColor(Color4f{ 0.0f, 0.0f, 1.0f, 1.0f });
	DrawPolygon(m_Vertices);
}

void Level::DrawForeground() const
{
	m_pForegroundTexture->Draw(m_FenceBottomLeft);
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const 
{
	Point2f actorBottomCenter{ actorShape.left + actorShape.width / 2, actorShape.bottom - 1 };
	Point2f actorTopCenter{ actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height };

	HitInfo hitInfo{};
	if (Raycast(m_Vertices, actorBottomCenter, actorTopCenter, hitInfo))
	{
		actorShape.bottom = hitInfo.intersectPoint.y;
		actorVelocity.y = 0;
		
	}
	m_pPlatform->HandleCollision(actorShape, actorVelocity);
}

bool Level::IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity) const
{
	Point2f actorBottomCenter{ actorShape.left + actorShape.width / 2, actorShape.bottom - 1 };
	Point2f actorTopCenter{ actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height };

	HitInfo hitInfo{};
	if (Raycast(m_Vertices, actorBottomCenter, actorTopCenter, hitInfo))
	{
		return true;
	}
	return m_pPlatform->IsOnGround(actorShape, actorVelocity);

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

Rectf Level::GetBoundaries() const
{
	return m_Boundaries;
}

bool Level::HasReachedEnd(const Rectf& actorshape)
{
	if (IsOverlapping(m_EndSignShape, actorshape))
	{
		m_EndReched = true;
		return true;
	}
	if (m_EndReched == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Level::DrawEnd() const
{
	if (m_EndReched)
	{
		SetColor(Color4f{ 0.0f, 0.0f, 0.0f, 0.4f });
		FillRect(0, 0, m_pBackgroundTexture->GetWidth(), m_pBackgroundTexture->GetHeight());
	}
}