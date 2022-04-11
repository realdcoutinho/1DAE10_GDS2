#include "pch.h"
#include "Player.h"
#include <iostream>
using namespace utils;

Player::Player(Point2f center, Point2f bottomLeft)
	: m_HorSpeed{ 60.0f }
	, m_JumpSpeed{ 185.0f }
	, m_Velocity{ 0.0f, 0.0f }
	//, m_Acceleration{ 0.0f, -981.0f }
	, m_Acceleration{ 0.0f, -325 }
	, m_Center{center}
	, m_State{State::rest}
	, m_pPlayerTexture{new Texture{"./Images/Player_v5.png"}}
	, m_BottomCenter{ bottomLeft }
	, m_NrOfColumns{ 4.f }
	, m_NrOfRows{11.f}
	, m_NrOfFrames{4}
	, m_NrOfFramesPerSec{ 10 }
	, m_AnimFrame{ 0 }
{
	SetMeasures();
	SetSourceRect();
	m_Shape=Rectf{ center.x - m_ClipWidth/2 + 4, center.y - m_ClipHeight/2, m_ClipWidth - 4, m_ClipHeight - 7 };
	std::cout << "Player was created" << '\n';

}

Player::~Player()
{
	delete m_pPlayerTexture;
}

void Player::SetHorizontalSpeed()
{

	switch (m_State)
	{
	case(State::jump):
		m_HorSpeed = 5;
		break;
	case(State::fall):
		m_HorSpeed = 18;
		break;
	case(State::run):
		m_HorSpeed = 60.f;
		break;
	}
}


void Player::Draw() const
{
	SetColor({ Color4f(0, 0, 1, 1) });
	Point2f actorBottomCenter{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom - 1 };
	Point2f actorTopCenter{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom + m_Shape.height };
	//FillRect(m_Shape);
	SetColor({ Color4f(1, 0, 1, 1) });
	DrawLine(actorBottomCenter, actorTopCenter, 4);

	Point2f textureBottomLeft{ m_BottomCenter.x - m_WidthTexture / 9 / 2, m_BottomCenter.y };
	//m_pPlayerTexture->Draw(m_BottomCenter, m_SourceRect);


	glPushMatrix();
	{
		glTranslatef(m_Shape.left, m_Shape.bottom, 0);
		if (!m_FacingLeft)
		{
			glScalef(-1, 1, 1);
			glTranslatef(-(m_Shape.width), 0, 0);
		}

		m_pPlayerTexture->Draw(Point2f{ 0.0f, 0.0f }, GetSourceRect());
	//	DrawLine(m_BottomCenter, m_BottomCenter, 4);
	}
	glPopMatrix();
}

void Player::SetState(int state)
{
	m_State = State(state);
}

Rectf Player::GetSourceRect() const
{
	return Rectf{ m_ClipWidth * m_AnimFrame, m_ClipHeight * -int(m_State), m_ClipWidth, m_ClipHeight };
}

void Player::SetMeasures()
{
	m_WidthTexture = m_pPlayerTexture->GetWidth();
	m_HeightTexture = m_pPlayerTexture->GetHeight();
	m_ClipWidth = m_pPlayerTexture->GetWidth() / m_NrOfColumns;
	m_ClipHeight = m_HeightTexture / m_NrOfRows;
}

void Player::SetSourceRect()
{
	m_SourceRect.left += 0;
	m_SourceRect.bottom += m_ClipWidth * int(m_State);
	m_SourceRect.width = m_ClipWidth;
	m_SourceRect.height = m_ClipHeight;
}

void Player::UpdateFrames(float elapsedSec)
{
	const float maxFrameTime{ 1.0f / m_NrOfFramesPerSec };
	m_AnimTime += elapsedSec;
	if (maxFrameTime < m_AnimTime)
	{
		m_AnimFrame = (m_AnimFrame + 1) % m_NrOfFrames;
		m_AnimTime -= maxFrameTime;
	}
}

Rectf Player::GetShape() const
{
	return m_Shape;
}

Vector2f Player::GetVelocity() const
{
	return m_Velocity;
}

void Player::Update(float elapsedSec, const Level* level)
{
	SetHorizontalSpeed();
	UpdateFrames(elapsedSec);
	const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
		UpdateHorizontalVelocity(elapsedSec, level, pKeysState);
		UpdateVerticalVelocity(elapsedSec, level, pKeysState);
		MoveAvatar(elapsedSec, level);
}

void Player::UpdateHorizontalVelocity(float elapsedSec, const Level* level, const Uint8* pKeysState)
{
	m_Velocity.x = 0;
	if (level->IsOnCloud(m_Shape, m_Velocity))
	{
		int index = level->GetCloudIndex();
		Vector2f cloudVelocity = level->GetCloudVelocityVector()[index];
		m_Velocity.x += cloudVelocity.x;
		if (pKeysState[SDL_SCANCODE_LEFT] || pKeysState[SDL_SCANCODE_A])
		{
			if (m_IsOnGround) {
				m_State = State::run;
			}
			m_Velocity.x = -m_HorSpeed;
			m_FacingLeft = true;
		}
		if (pKeysState[SDL_SCANCODE_RIGHT] || pKeysState[SDL_SCANCODE_D])
		{
			m_Velocity.x = m_HorSpeed * 2;
			if (m_IsOnGround) {
				m_State = State::run;
			}
			m_FacingLeft = false;
		}
	}
	if (pKeysState[SDL_SCANCODE_LEFT] || pKeysState[SDL_SCANCODE_A])
	{
		if(m_IsOnGround) {
			m_State = State::run;
		}
		m_Velocity.x = -m_HorSpeed;
		m_FacingLeft = true;
	}
	if (pKeysState[SDL_SCANCODE_RIGHT] || pKeysState[SDL_SCANCODE_D])
	{
		m_Velocity.x = m_HorSpeed;
		if (m_IsOnGround) {
			m_State = State::run;
		}
		m_FacingLeft = false;
	}

}

void Player::UpdateVerticalVelocity(float elapsedsec, const Level* level, const Uint8* pKeysState)
{
	level->HandleCollision(m_Shape, m_Velocity);
	if (pKeysState[SDL_SCANCODE_X] && level->IsOnGround(m_Shape, m_Velocity))
	{
		m_Velocity.y += m_JumpSpeed;
		m_State = State::jump;
	}
	if (pKeysState[SDL_SCANCODE_Z] && level->IsOnGround(m_Shape, m_Velocity))
	{
		m_State = State::kill;
	}
	m_IsOnGround = level->IsOnGround(m_Shape, m_Velocity);
}

void Player::MoveAvatar(float elapsedSec, const Level* level)
{
	if (m_Velocity.x != 0 || m_Velocity.y != 0)
	{
	}
	int index = level->GetCloudIndex();
	Vector2f cloudVelocity = level->GetCloudVelocityVector()[index];
	if (m_Velocity.x == cloudVelocity.x && m_Velocity.y == 0 && level->IsOnCloud(m_Shape, m_Velocity))
	{
		m_State = State::rest;
	}
	if (m_Velocity.x == 0 && m_Velocity.y == 0)
	{
		m_State = State::rest;
	}
	if ((m_Velocity.y < 50) && (!level->IsOnGround(m_Shape, m_Velocity)))
	{
		m_State = State::fall;
	}
	m_Velocity.y += m_Acceleration.y * elapsedSec ;
	m_Shape.left += m_Velocity.x * elapsedSec;
	//m_BottomCenter.x += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
	//m_BottomCenter.y += m_Velocity.y * elapsedSec;
	Clamp(level);
}

void Player::Clamp(const Level* level)
{
	const Rectf& boundaries{ level->GetBoundaries() };
	if (m_Shape.left < boundaries.left)
		m_Shape.left = boundaries.left;
	if (boundaries.left + boundaries.width < m_Shape.left + m_Shape.width)
		m_Shape.left = boundaries.left + boundaries.width - m_Shape.width;
}

bool Player::GetIsOnGround() const
{
	return m_IsOnGround;
}