#include "pch.h"
#include "Avatar.h"
#include <iostream>
using namespace utils;

Avatar::Avatar()
{

}

Avatar::Avatar(const Point2f& center, float width, float height)
	: m_Center{center}
	, m_Width{ width }
	, m_Height{ height }
{
	m_Speed = 200.f;
	std::cout << "Avatar created!" << '\n';
}

void Avatar::Update(float elapsedSec, Enemy** pEnemies, int numEnemies)
{
	HandleMoveKeyState(elapsedSec);

}



void Avatar::Draw()
{
	Color4f yellow{ 0, 1, 1, 1 };
	SetColor(yellow);
	Rectf avatar{ m_Center.x - m_Width / 2, m_Center.y - m_Height / 2, m_Width, m_Height};
	m_Avatar = avatar;

	DrawRect(m_Avatar, 3);
}


void Avatar::HandleMoveKeyState(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_Center.x += m_Speed * elapsedSec;
		std::cout << "Right   " << m_Center.x << '\n';
	}
	else if (pStates[SDL_SCANCODE_LEFT])
	{
		m_Center.x -= m_Speed * elapsedSec;
		std::cout << "Left   " << m_Center.x << '\n';
	}
}