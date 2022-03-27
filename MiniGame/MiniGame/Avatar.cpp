#include "pch.h"
#include "Avatar.h"
#include "Level.h"
#include <iostream>
using namespace utils;

Avatar::Avatar()
	: m_pSpritesTexture{ new Texture{"./resources/Images/AvatarSheet.png"} }
	, m_HorSpeed{ 200.0f }
	, m_JumpSpeed{ 600.0f }
	, m_AccuTransformSec{ 0.0f }
	, m_MaxTransformSec{ 1.0f }
	, m_ClipHeight{ 97.0f }
	, m_ClipWidth{ 72.0f }
	, m_Power{ 0 }
	, m_Acceleration{ 0.0f, -981.0f }
	, m_Velocity{ 0.0f, 0.0f }
	, m_ActionState{ ActionState::moving }
	, m_Shape{ 50.0f, 280.0f, 36.0f, 97.0f }
	, m_NrOfFrames{ 10 }
	, m_NrOfFramesPerSec{ 10 }
{
	if (!m_pSpritesTexture->IsCreationOk())
		std::cout << "Error loading Avatar spritesheet.\n";
}

Avatar::~Avatar()
{
	delete m_pSpritesTexture;
	m_pSpritesTexture = nullptr;
}

void Avatar::Update(float elapsedSec, const Level* pLevel)
{
	UpdateState(elapsedSec, pLevel);
	UpdateFrames(elapsedSec);
}

void Avatar::Draw()
{
	//DrawRectAvatar();
	DrawAvatarTexture();
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

void Avatar::DrawRectAvatar() const
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


	Point2f actorBottomCenter{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom - 1 };
	Point2f actorTopCenter{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom + m_Shape.height };

	SetColor(Color4f(0.0f, 1.0f, 0.0f, 1.0f));
	DrawLine(actorBottomCenter, actorTopCenter, 4);
}


void Avatar::UpdateState(float elapsedSec, const Level* pLevel)
{
	bool onGround{ pLevel->IsOnGround(m_Shape) };
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

	UpdateFrames(elapsedSec);
}

void Avatar::Transform(float elapsedSec)
{
	m_AccuTransformSec += elapsedSec;
	m_Velocity = Vector2f{ 0,0 };
	if (m_AccuTransformSec >= m_MaxTransformSec)
	{
		m_AccuTransformSec = 0;
		m_ActionState = ActionState::waiting;
	}
}

void Avatar::Move(float elapsedSec)
{
	m_Velocity = Vector2f{ 0,0 };
	m_ActionState = ActionState::moving;
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if ((pStates[SDL_SCANCODE_RIGHT]) || (pStates[SDL_SCANCODE_D]))
	{
		m_ActionState = ActionState::moving;
		m_Velocity.x = m_HorSpeed * elapsedSec;
	}
	if ((pStates[SDL_SCANCODE_LEFT]) || (pStates[SDL_SCANCODE_A]))
	{
		m_ActionState = ActionState::moving;
		m_Velocity.x = -m_HorSpeed * elapsedSec;
	}
	if ((pStates[SDL_SCANCODE_UP]) || (pStates[SDL_SCANCODE_W]))
	{
		m_ActionState = ActionState::moving;
		m_Velocity.y = m_JumpSpeed;
	}
}

void Avatar::UpdateFrames(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	if (m_AnimTime >= (1.0f / m_NrOfFramesPerSec))
	{
		++m_AnimFrame %= m_NrOfFrames;
		//++m_AnimFrame;
		//if (m_AnimFrame >= 10)
		//{
		//	m_AnimFrame = 0;
		//}
		//
		m_AnimTime = 0;
	}
	std::cout << m_AnimFrame << '\n';
	//std::cout << m_AnimTime << '\n';

	//m_Dest.left = m_ClipWidth * m_AnimFrame;
	//m_Dest.bottom = m_ClipHeight * (float(m_ActionState) + 1 + 3 * m_Power);

	m_Dest.left = (m_AnimFrame * m_ClipWidth);
	m_Dest.bottom = m_ClipHeight * (float(m_ActionState) + 1 + 3 * m_Power);

	m_Dest.width = m_ClipWidth;
	m_Dest.height = m_ClipHeight;

}

void Avatar::DrawAvatarTexture()
{
	m_pSpritesTexture->Draw(m_Shape, m_Dest);
}
