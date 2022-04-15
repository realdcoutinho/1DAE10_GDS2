#include "pch.h"
#include "Damage.h"
#include <iostream>

Damage::Damage(Point2f bottomLeft, int nrRows, int nrColumns, int nrFrames, int animFrame, float animTime, float nrFramesPerSec, float windowWidth)
	: GameObject(bottomLeft, nrRows, nrColumns)
	, m_WindowWidth{windowWidth}
	, m_NrOfFrames{ nrFrames }
	, m_AnimFrame{ animFrame }
	, m_AnimTime{ animTime }
	, m_NrOfFramesPerSec{ nrFramesPerSec }
{
	std::cout << "Damage created" << '\n';
}

void Damage::Draw() const
{

}

void Damage::Update(float elapsedSec)
{
	if (!m_IsOverlapping)
	{
		UpdateFrames(elapsedSec);
		UpdatePosition(elapsedSec);
	}
}

void Damage::UpdateFrames(float elapsedSec)
{
	const float maxFrameTime{ 1.0f / m_NrOfFramesPerSec };
	m_AnimTime += elapsedSec;
	if (maxFrameTime < m_AnimTime)
	{
		m_AnimFrame = (m_AnimFrame + 1) % m_NrOfFrames;
		m_AnimTime -= maxFrameTime;
	}
}

void Damage::UpdatePosition(float elapsedSec)
{
	m_BottomLeft.x += m_Velocity.x * elapsedSec;
	if (m_Velocity.x > 0)
		if (m_BottomLeft.x > m_WindowWidth + m_TextureWidth) // window width just to test it out
			m_BottomLeft.x = 0;
	if (m_Velocity.x < 0)
		if ((m_BottomLeft.x + m_TextureWidth) < 0)
			m_BottomLeft.x = m_WindowWidth + m_TextureWidth; // window width just to test it out
	////if ((!m_IsAlive) && m_Type == Type::typeThree)
	////{
	////	m_BottomLeft.y += m_Velocity.y * elapsedSec;
	////}

	m_DestRect = Rectf{ m_BottomLeft.x, m_BottomLeft.y, m_TextureSnipetWidth, m_TextureHeight };
}

void Damage::SetVelocity(Vector2f enemyVelocity)
{
	m_Velocity.x = enemyVelocity.x;
	m_Velocity.y = enemyVelocity.y;
}

void Damage::SetActorState(int state)
{
	m_ActorState = ActorState(state);
}

void Damage::SetWindowWidth(float windowWith)
{
	m_WindowWidth = windowWith;
}