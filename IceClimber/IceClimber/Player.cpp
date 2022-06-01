#include "pch.h"
#include "Player.h"
#include <iostream>
#include "Game.h"
using namespace utils;

Player::Player(Game* game, Point2f center, Point2f bottomLeft)
	: m_pGame			{game}
	, m_HorSpeed		{ 60.0f }
	, m_JumpSpeed		{ 190.0f }
	, m_Velocity		{ 0.0f, 0.0f }
	, m_Acceleration	{ 0.0f, -325 }
	, m_Center			{center}
	, m_State			{State::rest}
	, m_pPlayerTexture	{ game->GetTextureManager()->GetTexturePointer("Player")}
	, m_BottomCenter	{ bottomLeft }
	, m_NrOfColumns		{ 4.f }
	, m_NrOfRows		{11.f}
	, m_FacingLeft		{true}
	, m_IsOnGround		{ true }
	, m_IsWinning		{false}
	, m_Time			{0}
	, m_IsDead			{false}
{
	SetMeasures();
	InitializeAnimations();
}

Player::~Player()
{
	for (int i{ 0 }; i < m_NrAnimations; ++i)
	{
		delete m_Animations[i];
	}
}

void Player::InitializeAnimations()
{
	float framesPerSec{ 15.0f };

	m_Animations.push_back(new Animation(m_pPlayerTexture, int(State::roll), 0, 4, framesPerSec, 4, 11)); //roll //[0]
	m_Animations.push_back(new Animation(m_pPlayerTexture, int(State::dead), 0, 4, framesPerSec, 4, 11)); //dead //[1]
	m_Animations.push_back(new Animation(m_pPlayerTexture, int(State::jumpB), 0, 4, framesPerSec, 4, 11)); //jumpB //[2]
	m_Animations.push_back(new Animation(m_pPlayerTexture, int(State::runB), 0, 4, framesPerSec, 4, 11)); //runB //[3]
	m_Animations.push_back(new Animation(m_pPlayerTexture, int(State::restB), 0, 4, framesPerSec, 4, 11)); //restB //[4]
	m_Animations.push_back(new Animation(m_pPlayerTexture, int(State::kill), 0, 4, framesPerSec, 4, 11)); //kill //[5]
	m_Animations.push_back(new Animation(m_pPlayerTexture, int(State::fall), 0, 4, framesPerSec, 4, 11)); //fall //[6]
	m_Animations.push_back(new Animation(m_pPlayerTexture, int(State::jump), 0, 4, framesPerSec, 4, 11)); //jump //[7]
	m_Animations.push_back(new Animation(m_pPlayerTexture, int(State::slide), 0, 4, framesPerSec, 4, 11)); //slide //[8]
	m_Animations.push_back(new Animation(m_pPlayerTexture, int(State::run), 0, 4, framesPerSec, 4, 11)); //run //[9]
	m_Animations.push_back(new Animation(m_pPlayerTexture, int(State::rest), 0, 4, framesPerSec, 4, 11)); //rest //[10]
	m_NrAnimations = static_cast<int>(m_Animations.size());
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
	//case(State::dead):
	//	m_HorSpeed = 0;
	//	break;
	//case(State::roll):
	//	m_HorSpeed = 0;
	//	break;
	}
}


void Player::Draw() const
{
	Point2f actorBottomCenter{ m_Shape.GetBottomCenter(0, -1) };
	Point2f actorTopCenter{ m_Shape.GetBottomCenter(0, m_Shape.height) };
	SetColor({ Color4f(0, 0, 1, 1) });
	FillRect(m_Shape);

	SetColor({ Color4f(0, 1, 1, 1) });
	FillRect(m_ActorShape);

	SetColor({ Color4f(1, 0, 1, 1) });
	DrawLine(actorBottomCenter, actorTopCenter, 4);

	glPushMatrix();
	{
		glTranslatef(m_Shape.left - 5, m_Shape.bottom, 0);
		if (!m_FacingLeft)
		{
			glScalef(-1, 1, 1);
			glTranslatef(-(m_Shape.width) - 10, 0, 0);
		}
		switch (m_State)
		{
		case(State::rest):
			m_Animations[int(State::rest)]->Draw();
			break;
		case(State::run):
			m_Animations[int(State::run)]->Draw();
			break;
		case(State::slide):
			m_Animations[int(State::slide)]->Draw();
			break;
		case(State::jump):
			m_Animations[int(State::jump)]->Draw();
			break;
		case(State::fall):
			m_Animations[int(State::fall)]->Draw();
			break;
		case(State::kill):
			m_Animations[int(State::kill)]->Draw();
			break;
		case(State::restB):
			m_Animations[int(State::restB)]->Draw();
			break;
		case(State::runB):
			m_Animations[int(State::runB)]->Draw();
			break;
		case(State::jumpB):
			m_Animations[int(State::jumpB)]->Draw();
			break;
		case(State::dead):
			glRotatef(1, 1, 0, 0);
			m_Animations[int(State::dead)]->Draw();
			break;
		case(State::roll):
			m_Animations[int(State::roll)]->Draw();
			break;
		}
	}
	glPopMatrix();
}

void Player::UpdateTimeState(float elapsedSec)
{
	if (m_State == State::dead || m_IsDead)
	{
		m_IsDead = true;
		m_Time += elapsedSec;
		if (m_Time < 1.5f)
		{
			m_State = State::roll;
			m_Time = 0;
		}
	}
}

void Player::UpdateDyingMovement(float elapsedSec)
{

}


int Player::GetPlayerState()
{
	return int(m_State);
}

void Player::SetState(int state)
{
	m_State = State(state);
}

void Player::SetMeasures()
{
	m_WidthTexture = m_pPlayerTexture->GetWidth();
	m_HeightTexture = m_pPlayerTexture->GetHeight();
	m_ClipWidth = m_pPlayerTexture->GetWidth() / m_NrOfColumns;
	m_ClipHeight = m_HeightTexture / m_NrOfRows;
	m_Shape = Rectf{ m_Center.x, m_Center.y, 10, 20 };
	m_ActorShape = Rectf{ };
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
	if (!m_IsWinning)
	{
		UpdateDyingMovement(elapsedSec);
		UpdateAnimations(elapsedSec);
		UpdateTimeState(elapsedSec);
		SetHorizontalSpeed();

		const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
		UpdateHorizontalVelocity(elapsedSec, level, pKeysState);
		UpdateVerticalVelocity(elapsedSec, level, pKeysState);

		if ((m_State != State::dead) && (m_State != State::roll))
		{
			MoveAvatar(elapsedSec, level);
		}
	}
}

void Player::UpdateHorizontalVelocity(float elapsedSec, const Level* level, const Uint8* pKeysState)
{
	m_Velocity.x = 0;
	if ((m_State == State::dead) || (m_State == State::roll))
	{
		m_Velocity.x = 0;
	}
	else 
	{
		if (level->IsOnCloud(m_Shape, m_Velocity))
		{
			Vector2f cloudVelocity = level->GetCloudVelocityVector();
			m_Velocity.x += cloudVelocity.x;
			if (pKeysState[SDL_SCANCODE_LEFT] || pKeysState[SDL_SCANCODE_A])
			{
				if (m_IsOnGround)
					m_State = State::run;
				if (cloudVelocity.x > 0)
					m_Velocity.x += cloudVelocity.x;

				m_FacingLeft = true;
			}
			if (pKeysState[SDL_SCANCODE_RIGHT] || pKeysState[SDL_SCANCODE_D])
			{
				if (m_IsOnGround)
					m_State = State::run;
				if (cloudVelocity.x < 0)
					m_Velocity.x += cloudVelocity.x;
				m_FacingLeft = false;
			}
		}
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
			m_Velocity.x = m_HorSpeed;
			if (m_IsOnGround) {
				m_State = State::run;
			}
			m_FacingLeft = false;
		}
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
	if (m_State == State::roll)
	{
		m_Velocity.y += 200.0f;
	}
	m_IsOnGround = level->IsOnGround(m_Shape, m_Velocity);
}

void Player::MoveAvatar(float elapsedSec, const Level* level)
{
	if (m_Velocity.x != 0 || m_Velocity.y != 0)
	{
	}
	Vector2f cloudVelocity = level->GetCloudVelocityVector();
	if (m_Velocity.x == cloudVelocity.x && m_Velocity.y == 0 && level->IsOnCloud(m_Shape, m_Velocity))
	{
		m_State = State::rest;
	}
	if (m_Velocity.x == 0 && m_Velocity.y == 0 && m_State != State::kill)
	{
		m_State = State::rest;
	}
	if ((m_Velocity.y < 50) && (!level->IsOnGround(m_Shape, m_Velocity)))
	{
		m_State = State::fall;
	}
	m_Velocity.y += m_Acceleration.y * elapsedSec ;
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
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

void Player::SetWinning(bool isWinning)
{
	m_IsWinning = isWinning;
}

void Player::UpdateAnimations(float elapsedSec)
{
	for (int i{ 0 }; i < m_NrAnimations; ++i)
	{
		m_Animations[i]->Update(elapsedSec);
	}
}