#include "pch.h"
#include "Avatar.h"
#include "Level.h"
#include <iostream>
using namespace utils;

Avatar::Avatar()
{

}

Avatar::~Avatar()
{

}

void Avatar::Update(float elapsedSec, const Level* pLevel)
{
	bool onGround{ pLevel->IsOnGround(m_Shape)};
	if (m_ActionState == ActionState::transforming)
	{
		Transform(elapsedSec);
	}
	if (onGround) 
	{
		Move(elapsedSec);
	}
	else
	{
		m_Velocity += m_Acceleration * elapsedSec;
	}
	m_Shape.left += m_Velocity.x;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
}

void Avatar::Draw()
{
	Color4f waitYellow{ 1.0f, 1.0f, 0.0f, 1.f };
	Color4f moveRed{ 1.0f, 0.0f, 0.0f, 1.f };
	Color4f transformBlue{ 0.0f, 0.0f, 1.0f, 1.f };

	switch (m_ActionState)
	{
	case(ActionState::waiting):
		SetColor(waitYellow);
		FillRect(m_Shape);
		break;
	case(ActionState::moving):
		SetColor(moveRed);
		FillRect(m_Shape);
		break;
	case(ActionState::transforming):
		SetColor(transformBlue);
		FillRect(m_Shape);
		break;
	}

	for (int i{ 0 }; i < m_Power; ++i)
	{
		SetColor(Color4f{ 0,0,0,1 });
		float offset{ 5 };
		float side{ 5 };
		FillRect(m_Shape.left + offset, m_Shape.bottom + offset + i * offset + i * side, side, side);
	}
}

void Avatar::PowerUpHit()
{
	m_ActionState = ActionState::transforming;
	++m_Power;
}

Rectf Avatar::GetShape()
{
	return m_Shape;
}

void Avatar::Transform(float elapsedSec)
{
	m_AccuTransformSec += elapsedSec;
	m_Velocity = Vector2f{ 0,0 };
	std::cout << " transform  " << m_Shape.bottom << '\n';
	if (m_AccuTransformSec >= m_MaxTransformSec)
	{
		m_AccuTransformSec = 0;
		m_ActionState = ActionState::moving;
		std::cout << " done transform" << '\n';
	}
}

void Avatar::Move(float elapsedSec)
{
	m_Velocity = Vector2f{ 0,0 };
	m_ActionState = ActionState::waiting;
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_ActionState = ActionState::moving;
		m_Velocity.x = m_HorSpeed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_LEFT])
	{
		m_ActionState = ActionState::moving;
		m_Velocity.x = -m_HorSpeed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_UP])
	{
		m_ActionState = ActionState::moving;
		m_Velocity.y = m_JumpSpeed;
	}
}
