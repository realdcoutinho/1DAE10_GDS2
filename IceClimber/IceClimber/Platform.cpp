#include "pch.h"
#include "Platform.h"
#include <iostream>
using namespace utils;

Platform::Platform(Point2f bottomLeft, int nrOfRows, int nrOfColumns, int type, int nrLenght, float windowWidth, bool isMovable)
	: GameObject(bottomLeft, nrOfRows, nrOfColumns)
	, m_Type{Type(type)}
	, m_NrLenght{ nrLenght }
	, m_WindowWidth{ windowWidth }
	, m_IsMovable{isMovable}
	, m_IsDestroyed{false}
	, m_TotalWidth{0} // it will be redefined later on
{
}

Platform::~Platform()
{

}

void Platform::Draw() const
{
}



void Platform::Update(float elapsedSec)
{
	if (m_IsMovable)
	{
		SetCollision();
		UpdatePosition(elapsedSec);
	}
}

void Platform::UpdatePosition(float elapsedSec)
{
	m_BottomLeft.x += m_Velocity.x * elapsedSec;

	if (m_Velocity.x > 0)
		if (m_BottomLeft.x > m_WindowWidth)
			m_BottomLeft.x = -(m_TotalWidth);
	if (m_Velocity.x < 0)
		if (m_BottomLeft.x + m_TotalWidth < 0)
			m_BottomLeft.x = m_WindowWidth;
}

void Platform::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	Point2f actorBottomCenter{ actorShape.GetBottomCenter(0, -1) };
	Point2f actorTopCenter{ actorShape.GetTopCenter() };




	HitInfo hitInfo{};
	if (Raycast(m_TopLine, actorBottomCenter, actorTopCenter, hitInfo) && actorVelocity.y <= 0 && hitInfo.lambda < 0.5f) //if hit from the top
	{
		actorShape.bottom = hitInfo.intersectPoint.y; //actor will ahve the same height as the intercection point
		actorVelocity.y = 0; //his velocity y will now be 0
	}
	if (Raycast(m_BottomLine, actorTopCenter, actorBottomCenter, hitInfo) && actorVelocity.y > 0) //if hit from bellow
	{
		actorVelocity.y = -actorVelocity.y; //IT JUST WORKS FOR THE ANIMATION, DONT TOUCH FFS; //IT JUST WORKS FOR THE ANIMATION, DONT TOUCH FFS
		
		if (!m_IsMovable)
		{
			actorVelocity.y = 5; //IT JUST WORKS FOR THE ANIMATION, DONT TOUCH FFS
			m_Collision.clear(); //Clears collsion because it was just destroyd
			m_TopLine.clear();
			m_BottomLine.clear();
			m_IsDestroyed = true; // sets the variable to true. meaning it wont be drawn
		}
	}
}

bool Platform::IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity) const
{
	Point2f actorBottomCenter{ actorShape.GetBottomCenter(0, -1) };
	Point2f actorTopCenter{ actorShape.GetTopCenter() };

	HitInfo hitInfo{};
	return (Raycast(m_TopLine, actorBottomCenter, actorTopCenter, hitInfo) && actorVelocity.y <= 0 && hitInfo.lambda < 0.5f); //returns a value if the player is on top
}

bool Platform::IsOnGround(const Rectf& actorShape) const
{
	Point2f actorBottomCenter{ actorShape.GetBottomCenter(0, -1) };
	Point2f actorTopCenter{ actorShape.GetTopCenter() };

	HitInfo hitInfo{};
	return (Raycast(m_TopLine, actorBottomCenter, actorTopCenter, hitInfo) && hitInfo.lambda < 0.5f);
}

bool Platform::IsOnGroundStalgmite(const Rectf& actorShape) const
{
	Point2f actorBottomCenter{ actorShape.GetBottomCenter(0, -1) };
	Point2f actorTopCenter{ actorShape.GetTopCenter() };
	std::vector<Point2f> line;
	line.push_back(Point2f{ m_BottomLeft.x, m_BottomLeft.y + m_TextureSnipetHeight });
	line.push_back(Point2f{ m_BottomLeft.x + (m_TextureSnipetWidth * m_NrLenght), m_BottomLeft.y + m_TextureSnipetHeight });
	HitInfo hitInfo{};
	return (Raycast(line, actorBottomCenter, actorTopCenter, hitInfo) && hitInfo.lambda < 0.5f);
}

void Platform::SetCollision()
{
	m_Collision.clear();
	m_Collision.push_back(m_BottomLeft);
	m_Collision.push_back(Point2f{ m_BottomLeft.x + (m_TextureSnipetWidth * m_NrLenght), m_BottomLeft.y });
	m_Collision.push_back(Point2f{ m_BottomLeft.x + (m_TextureSnipetWidth * m_NrLenght), m_BottomLeft.y + m_TextureSnipetHeight });
	m_Collision.push_back(Point2f{ m_BottomLeft.x, m_BottomLeft.y + m_TextureSnipetHeight });
	SetLines();
}

void Platform::SetLines() 
{
	m_BottomLine.clear();
	m_TopLine.clear();

	m_BottomLine.push_back(m_BottomLeft);
	m_BottomLine.push_back(Point2f{ m_BottomLeft.x + (m_TextureSnipetWidth * m_NrLenght), m_BottomLeft.y });

	m_TopLine.push_back(Point2f{ m_BottomLeft.x, m_BottomLeft.y + m_TextureSnipetHeight });
	m_TopLine.push_back(Point2f{ m_BottomLeft.x + (m_TextureSnipetWidth * m_NrLenght), m_BottomLeft.y + m_TextureSnipetHeight });
}



void Platform::SetVelocity()
{

}
