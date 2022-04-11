#include "pch.h"
#include "Cloud.h"
#include <iostream>
using namespace utils;

int Cloud::m_InstanceCounter{ 0 };


Cloud::Cloud(Point2f bottomLeft, int nrLenght, int type, float windowWidth)
	:Platform{bottomLeft}
	, m_NrLenght{ nrLenght}
	, m_NrOfTypesBlocks{2}
	, m_MaxVelocityX{60}
	, m_MinVelocityX{30}
	, m_WindowWidth{ windowWidth }
	, m_Type{CloudType(type)}
	, m_pCloud{new Texture{"./Images/Clouds.png"}}
{
	SetMeasures();
	SetSourceRect();
	SetCollision(); 
	SetVelocity();
	++m_InstanceCounter;
}

Cloud::~Cloud()
{
	delete m_pCloud;
}

void Cloud::SetMeasures()
{
	m_FullTextureWidth = m_pCloud->GetWidth();
	m_TextureOneCloud = m_FullTextureWidth / m_NrOfTypesBlocks;
	m_TextureCloudSnipet = m_TextureOneCloud / 3.0f; // 3 because the cloud is divided into three areas (left center and right)
	m_TextureHeight = m_pCloud->GetHeight();
	m_TotalCouldWidth = m_TextureCloudSnipet * 2.0f + m_TextureCloudSnipet * m_NrLenght; // two because of the left and right snipet
}

void Cloud::SetSourceRect()
{
	if (m_Type == CloudType::bottom)
	{
		m_SourceRect.left = 0.0f;
		m_SourceRect.bottom = -0.05f; //fixes offset
		m_SourceRect.width = m_TextureCloudSnipet;
		m_SourceRect.height = m_TextureHeight;
	}
	if (m_Type == CloudType::top)
	{
		m_SourceRect.left = m_FullTextureWidth / m_NrOfTypesBlocks;
		m_SourceRect.bottom = -0.05f; //fixes offset
		m_SourceRect.width = m_TextureCloudSnipet;
		m_SourceRect.height = m_TextureHeight;
	}
}

void Cloud::SetCollision()
{
	m_CloudCollision.clear(); // clears the std::vector before intruducing a point2fs
	Point2f p1{ m_BottomLeft };
	Point2f p2{ m_BottomLeft.x + (m_TextureCloudSnipet)+(m_TextureCloudSnipet * m_NrLenght) + m_TextureCloudSnipet, m_BottomLeft.y };
	Point2f p3{ m_BottomLeft.x + (m_TextureCloudSnipet)+(m_TextureCloudSnipet * m_NrLenght) + m_TextureCloudSnipet, m_BottomLeft.y + m_TextureHeight };
	Point2f p4{ m_BottomLeft.x, m_BottomLeft.y + m_TextureHeight };

	m_CloudCollision.push_back(p1);
	m_CloudCollision.push_back(p2);
	m_CloudCollision.push_back(p3);
	m_CloudCollision.push_back(p4);
}

void Cloud::SetVelocity()
{
	float velocityX = float(m_MinVelocityX + (std::rand() % (m_MaxVelocityX - m_MinVelocityX + 1))); //gets a random value betweeen 60 and 30

	if (m_InstanceCounter % 2 == 0)
		m_Velocity = Vector2f{ velocityX , 0 }; //if the the cloud is even it will move to the right

	if (m_InstanceCounter % 2 != 0)
		m_Velocity = Vector2f{ velocityX * -1, -0 }; // if the cloud is odd it will move to the left

}

void Cloud::Update(float elapsedSec)
{
	SetCollision();
	UpdateCloudPosition(elapsedSec);
}

void Cloud::Draw() const
{
	Rectf sourceRect{ m_SourceRect }; //this method assures that the m variables is never altered
	Point2f bottomLeft{ m_BottomLeft }; //this method assures that the m variables is never altered
	glPushMatrix();
	{
		DrawLeftTexture(bottomLeft, sourceRect); //draws left
		DrawCenterTexture(bottomLeft, sourceRect); //draws center
		DrawRightTexture(bottomLeft, sourceRect); //draws right
	}
	glPopMatrix();
}

void Cloud::UpdateCloudPosition(float elapsedSec)
{
	m_BottomLeft.x += m_Velocity.x * elapsedSec;

	if (m_Velocity.x > 0)
		if (m_BottomLeft.x > m_WindowWidth)
			m_BottomLeft.x = -(m_TotalCouldWidth);
	if (m_Velocity.x < 0)
		if (m_BottomLeft.x + m_TotalCouldWidth < 0)
			m_BottomLeft.x = m_WindowWidth;
}

Vector2f Cloud::GetVelocity() const
{
	return m_Velocity;
}

void Cloud::DrawLeftTexture(Point2f& bottomLeft, Rectf& sourceRect) const
{
	m_pCloud->Draw(m_BottomLeft, sourceRect);
	bottomLeft.x += m_TextureCloudSnipet; //adds a texture snipet width to the position x
	sourceRect.left += m_TextureCloudSnipet; //adds a texture snipet width to the position x
}

void Cloud::DrawCenterTexture(Point2f& bottomLeft, Rectf& sourceRect) const
{
	for (int i{}; i < m_NrLenght; ++i)
	{
		m_pCloud->Draw(bottomLeft, sourceRect);
		bottomLeft.x += m_TextureCloudSnipet;//adds a texture snipet width to the position x
	}
	sourceRect.left += m_TextureCloudSnipet; //adds a texture snipet width to the position x
	//since it will be drawing the same area i times, then only update the source rect to the last bit at the end
}

void Cloud::DrawRightTexture(Point2f& bottomLeft, Rectf& sourceRect) const
{
	m_pCloud->Draw(bottomLeft, sourceRect);
}



void Cloud::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	Point2f actorBottomCenter{ actorShape.GetBottomCenter(0, -1)};
	Point2f actorTopCenter{ actorShape.GetTopCenter()};

	HitInfo hitInfo{};
	if (Raycast(m_CloudCollision, actorBottomCenter, actorTopCenter, hitInfo) && actorVelocity.y <= 0)
	{
		actorShape.bottom = hitInfo.intersectPoint.y;
		actorVelocity.y = 0;
	}
	if (Raycast(m_CloudCollision, actorTopCenter, actorBottomCenter, hitInfo) && actorVelocity.y > 0)
	{
		actorVelocity.y = -actorVelocity.y;
	}
}

bool Cloud::IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity) const
{
	Point2f actorBottomCenter{ actorShape.GetBottomCenter(0, -1) };
	Point2f actorTopCenter{ actorShape.GetTopCenter() };

	HitInfo hitInfo{};
	return (Raycast(m_CloudCollision, actorBottomCenter, actorTopCenter, hitInfo) && actorVelocity.y <= 0);
}

bool Cloud::IsOnGround(const Rectf& actorShape) const
{
	Point2f actorBottomCenter{ actorShape.GetBottomCenter(0, -1) };
	Point2f actorTopCenter{ actorShape.GetTopCenter() };

	HitInfo hitInfo{};
	return (Raycast(m_CloudCollision, actorBottomCenter, actorTopCenter, hitInfo));
}






