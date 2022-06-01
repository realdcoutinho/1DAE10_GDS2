#include "pch.h"
#include "NPC.h"
#include <iostream>
using namespace utils;

NPC::NPC(Point2f bottomLeft, float windowWidth, int nrRows, int nrColumns, int nrOfFrames, int animFrame, float animTime, float nrOfFramesPerSec)
	: m_BottomLeft{ bottomLeft }
	, m_WindowWidth{ windowWidth }
	, m_NrRows{nrRows}
	, m_NrColumns{nrColumns}
	, m_AnimFrame{animFrame}
	, m_AnimTime{animTime}
	, m_NrOfFrames{nrOfFrames}
	, m_NrOfFramesPerSec{ nrOfFramesPerSec }
	, m_IsOverlapping{false}
	, m_IsAlive{true}
{

}

NPC::~NPC()
{

}

void NPC::Draw() const
{

}

void NPC::Update(float elapsedSed)
{

}

bool NPC::Overlap(const Rectf& actorShape)
{
	if (IsOverlapping(actorShape, m_CollisionRect))
	{
		m_IsOverlapping = true;
		return true;
	}
	return false;
}


void NPC::SetMeasures(float textureWidth, float textureHeight, float textureWidthSnipet, float textureHeightSnipet, Rectf destRect)
{
	m_TextureWidth = textureWidth;
	m_TextureHeight = textureHeight;
	m_TextureWidthSnipet = textureWidthSnipet;
	m_TextureHeightSnipet = textureHeightSnipet;
	m_CollisionRect = destRect;
}

void NPC::UpdatePosition(float elapsedSec)
{
	m_BottomLeft.x += m_Velocity.x * elapsedSec;
	if (m_Velocity.x > 0)
		if (m_BottomLeft.x > m_WindowWidth)
		{
			m_BottomLeft.x = -m_TextureWidthSnipet;
			if (!m_IsAlive)
			{
				m_IsAlive = true;
			}
		}
	if (m_Velocity.x < 0)
		if (m_BottomLeft.x + m_TextureWidthSnipet < 0)
		{
			m_BottomLeft.x = m_WindowWidth + m_TextureWidthSnipet;
			if (!m_IsAlive)
			{
				m_IsAlive = true;
			}
		}

	if ((!m_IsAlive) && m_Type == Type::typeThree)
	{
		m_BottomLeft.y += m_Velocity.y * elapsedSec;
	}

	m_CollisionRect = Rectf{ m_BottomLeft.x, m_BottomLeft.y, m_TextureWidthSnipet, m_TextureHeightSnipet };
}

void NPC::SetVelocity(float horSpeed)
{
	int rand = std::rand() % 100;

	if (rand % 2 == 0)
		m_Velocity = Vector2f{ horSpeed , -75 }; 

	if (rand % 2 != 0)
		m_Velocity = Vector2f{ horSpeed * -1, -75 }; 
}
