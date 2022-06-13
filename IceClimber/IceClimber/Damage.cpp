#include "pch.h"
#include "Damage.h"
#include <iostream>

using namespace utils;

Damage::Damage(Point2f bottomLeft, int type, int nrRows, int nrColumns, int nrFrames, int animFrame, float animTime, float nrFramesPerSec, float windowWidth)
	: GameObject(bottomLeft, nrRows, nrColumns)
	, m_NrOfFrames{ nrFrames }
	, m_AnimFrame{ animFrame }
	, m_AnimTime{ animTime }
	, m_NrOfFramesPerSec{ nrFramesPerSec }
	, m_Type{static_cast<Type>(type)}
	, m_WindowWidth{}
	, m_WindowLeft{}
	, m_ActorState{}
{

}

void Damage::Draw() const
{

}

void Damage::Update(float elapsedSec)
{
	switch (m_Type)
	{
	case(Type::horizontal):
		UpdateHorizontalPosition(elapsedSec);
		break;
	case(Type::vertical):
		UpdateVerticalPosition(elapsedSec);
		break;
	}
}

void Damage::SetVelocity(Vector2f enemyVelocity)
{
	switch (m_Type)
	{
	case(Type::horizontal):
		m_Velocity.x = enemyVelocity.x;
		m_Velocity.y = 0;
		break;
	case(Type::vertical):
		m_Velocity.x = 0;
		m_Velocity.y = 0;
		break;
	}
}

void Damage::SetActorState(int state)
{
	m_ActorState = ActorState(state);
}

void Damage::SetWindowWidth(Rectf gameRect)
{
	m_WindowLeft = gameRect.left;
	m_WindowWidth = gameRect.width;
}

void Damage::UpdateHorizontalPosition(float elapsedSec)
{
	m_BottomLeft.x += m_Velocity.x * elapsedSec;
	if (m_Velocity.x > 0)
		if (m_BottomLeft.x > m_WindowLeft + m_WindowWidth + m_TextureWidth) // window width just to test it out
			m_BottomLeft.x = m_WindowLeft;
	if (m_Velocity.x < 0)
		if ((m_BottomLeft.x + m_TextureWidth) < m_WindowLeft)
			m_BottomLeft.x = m_WindowWidth + m_WindowLeft; // window width just to test it out

	m_DestRect = Rectf{ m_BottomLeft.x, m_BottomLeft.y, m_TextureSnipetWidth, m_TextureSnipetHeight };
}

void Damage::UpdateVerticalPosition(float elapsedSec)
{
	if (m_Velocity.y < 0)
			m_BottomLeft.y += m_Velocity.y * elapsedSec;
	m_DestRect = Rectf{ m_BottomLeft.x, m_BottomLeft.y, m_TextureSnipetWidth, m_TextureSnipetHeight };
}


