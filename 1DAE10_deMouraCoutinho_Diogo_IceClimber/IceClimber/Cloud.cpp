#include "pch.h"
#include "Cloud.h"
#include <iostream>
#include "Level.h"
using namespace utils;

int Cloud::m_InstanceCounter{ 0 };


Cloud::Cloud(Level* level, Point2f bottomLeft, int nrLenght, int type, float windowWidth)
	:Platform{bottomLeft, 2, 3, type, nrLenght, windowWidth, true }
	, m_MaxVelocityX{60}
	, m_MinVelocityX{30}
	//, m_pCloud{new Texture{"./Images/Clouds.png"}}
	, m_pCloud{ level->GetTextureManager()->GetTexturePointer("Cloud") }
{
	SetMeasures();
	++m_InstanceCounter;
}

Cloud::~Cloud()
{
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

void Cloud::DrawLeftTexture(Point2f& bottomLeft, Rectf& sourceRect) const
{
	m_pCloud->Draw(m_BottomLeft, sourceRect);
	bottomLeft.x += m_TextureSnipetWidth; //adds a texture snipet width to the position x
	sourceRect.left += m_TextureSnipetWidth; //adds a texture snipet width to the position x
}

void Cloud::DrawCenterTexture(Point2f& bottomLeft, Rectf& sourceRect) const
{
	for (int i{}; i < m_NrLenght - 2; ++i) //removes the first and the last texture -2
	{
		m_pCloud->Draw(bottomLeft, sourceRect);
		bottomLeft.x += m_TextureSnipetWidth;//adds a texture snipet width to the position x
	}
	sourceRect.left += m_TextureSnipetWidth; //adds a texture snipet width to the position x
	//since it will be drawing the same area i times, then only update the source rect to the last bit at the end
}

void Cloud::DrawRightTexture(Point2f& bottomLeft, Rectf& sourceRect) const
{
	m_pCloud->Draw(bottomLeft, sourceRect);
}

void Cloud::SetVelocity()
{
	float velocityX = float(m_MinVelocityX + (std::rand() % (m_MaxVelocityX - m_MinVelocityX + 1))); //gets a random value betweeen 60 and 30

	if (m_InstanceCounter % 2 == 0)
		m_Velocity = Vector2f{ velocityX , 0 }; //if the the cloud is even it will move to the right

	if (m_InstanceCounter % 2 != 0)
		m_Velocity = Vector2f{ velocityX * -1, -0 }; // if the cloud is odd it will move to the left
}

void Cloud::SetMeasures()
{
	m_TextureWidth = m_pCloud->GetWidth();
	m_TextureHeight = m_pCloud->GetHeight();
	m_TextureSnipetWidth = m_TextureWidth / m_NrColumns;
	m_TextureSnipetHeight = m_TextureHeight / m_NrRows;
	m_TotalWidth = m_TextureSnipetWidth * m_NrLenght;
	//
	m_DestRect = Rectf{ m_BottomLeft.x, m_BottomLeft.y, m_TextureSnipetWidth, m_TextureSnipetHeight };
	//
	m_SourceRect.left = 0;
	m_SourceRect.bottom = m_TextureSnipetHeight * -int(m_Type);
	m_SourceRect.width = m_TextureSnipetWidth;
	m_SourceRect.height = m_TextureSnipetHeight;
	SetVelocity();
}

Vector2f Cloud::GetVelocity() const
{
	return m_Velocity;
}

float Cloud::GetWidth() const
{
	return m_TextureSnipetWidth;
}

float Cloud::GetHeight() const
{
	return m_TextureSnipetHeight;
}





