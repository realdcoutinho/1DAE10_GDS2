#include "pch.h"
#include "Blocks.h"
#include <iostream>
using namespace utils;

Blocks::Blocks(Point2f bottomLeft, int nrOfTypes, int type)
	:Platform{ bottomLeft }
	, m_pBlocks{new Texture{"./Images/IC_Blocks.png"}}
	, m_NrOfTypesBlocks{nrOfTypes}
	, m_Type{ BlockType(type)}
	, m_IsDestroyed{false}
{
	SetMeasures();
	SetSourceRect();
	SetCollision();
	std::cout << "Base Block created" << '\n';
}

Blocks::~Blocks()
{
	delete m_pBlocks;
}

void Blocks::SetMeasures()
{
	m_Width = (m_pBlocks->GetWidth()) / m_NrOfTypesBlocks; //individual block width
	m_Height = (m_pBlocks->GetHeight()); // individual block height
}

void Blocks::SetSourceRect()
{
	m_SourceRect.left = (m_Width) * int(m_Type); //the .left will be dependent on the type
	m_SourceRect.bottom = 0;
	m_SourceRect.width = m_Width;
	m_SourceRect.height = m_Height;
}

void Blocks::SetCollision()
{
	m_BlockCollision.push_back(m_BottomLeft);
	m_BlockCollision.push_back(Point2f{ m_BottomLeft.x , m_BottomLeft.y + m_Height });
	m_BlockCollision.push_back(Point2f{ m_BottomLeft.x + m_Width , m_BottomLeft.y + m_Height });
	m_BlockCollision.push_back(Point2f{ m_BottomLeft.x + m_Width, m_BottomLeft.y });
}

void Blocks::Draw() const
{
	if (!m_IsDestroyed) //if no destroyed, fraw
		m_pBlocks->Draw(m_BottomLeft, m_SourceRect);
}

float Blocks::GetWidth() const
{
	return m_Width;
}
float Blocks::GetHeight() const
{
	return m_Height;
}

void Blocks::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	Point2f actorBottomCenter{ actorShape.GetBottomCenter(0, -1) };
	Point2f actorTopCenter{ actorShape.GetBottomCenter(0, actorShape.height) };

	HitInfo hitInfo{};
	if (Raycast(m_BlockCollision, actorBottomCenter, actorTopCenter, hitInfo) && actorVelocity.y <= 0) //if hit from the top
	{
		actorShape.bottom = hitInfo.intersectPoint.y; //actor will ahve the same height as the intercection point
		actorVelocity.y = 0; //his velocity y will now be 0
	}
	if (Raycast(m_BlockCollision, actorTopCenter, actorBottomCenter, hitInfo) && actorVelocity.y > 0) //if hit from bellow
	{
		actorVelocity.y = 25; //IT JUST WORKS FOR THE ANIMATION, DONT TOUCH FFS
		m_BlockCollision.clear(); //Clears collsion because it was just destroyd
		m_IsDestroyed = true; // sets the variable to true. meaning it wont be drawn
	}
}

bool Blocks::IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity) const
{
	Point2f actorBottomCenter{ actorShape.GetBottomCenter(0, -1)};
	Point2f actorTopCenter{ actorShape.GetBottomCenter(0,actorShape.height) };

	HitInfo hitInfo{};
	return (Raycast(m_BlockCollision, actorBottomCenter, actorTopCenter, hitInfo) && actorVelocity.y <= 0); //returns a value if the player is on top
}



