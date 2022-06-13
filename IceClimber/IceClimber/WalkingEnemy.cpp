#include "pch.h"
#include "WalkingEnemy.h"
#include "Level.h"
#include "Player.h"
#include <iostream>
using namespace utils;


int WalkingEnemy::m_NrOfEnemy{ 0 };

WalkingEnemy::WalkingEnemy(Player* player, Level* level, Point2f bottomLeft, float windowWidth)
	: NPC(player, level, bottomLeft, windowWidth, 3, 4, 4, 0, 0, 10)
	, m_pEnemiesAlive{level->GetTextureManager()->GetTexturePointer("EnemyAlive")}
	, m_pEnemiesDead{level->GetTextureManager()->GetTexturePointer("EnemyDead")}
	, m_IsOnGround{}
	, m_HorSpeed{ 25.0f }
	, m_Acceleration{ 0.0f, -200 }
	, m_InitialHeight{ bottomLeft.y}
	, m_NeedsStalagmite{false}
	, m_IsOffScreen{false}
	, m_HasStalagmite{false}
	, m_StalagmiteCreated{ false }
	, m_TimeToDestroy{}
	, m_VelocityXFlipped{}
{
	++m_NrOfEnemy;
	SetMeasures();
	SetEnemyType();
	InitializeAnimations();
	SetVelocity();

}

void WalkingEnemy::Update(float elapsedSec)
{
	UpdateStalagmites(elapsedSec);
	m_ActorShape = m_pPlayer->GetShape();
	m_ActorState = State(m_pPlayer->GetPlayerState());
	m_IsOnGround = m_pGameLevel->IsOnGround(m_CollisionRect, m_Velocity);
	if (!m_IsOverlapping)
	{
		UpdateVerticalVelocity(elapsedSec);
		UpdateHorizontalVelocity(elapsedSec);
		UpdateAnimations(elapsedSec);
		UpdatePosition(elapsedSec);
	}
	UpdateCollisionTools();
}

void WalkingEnemy::UpdateVerticalVelocity(float elapsedSec)
{
	m_pGameLevel->HandleCollision(m_CollisionRect, m_Velocity);
	if (!(m_pGameLevel->IsOnGround(m_CollisionRect, m_Velocity)))
	{
		m_NeedsStalagmite = true;
	}
	m_IsOnGround = m_pGameLevel->IsOnGround(m_CollisionRect, m_Velocity);
	if (!m_IsOnGround)
		m_Velocity.y += m_Acceleration.y * elapsedSec;
}

void WalkingEnemy::UpdateHorizontalVelocity(float elapsedSec)
{

}

void WalkingEnemy::UpdatePosition(float elapsedSec)
{
	if (m_IsOnGround)
	{
		m_BottomLeft.x += m_Velocity.x * elapsedSec;
		if (m_Velocity.x > 0)
			if (m_CollisionRect.left > m_WindowBoundries.left + m_WindowBoundries.width)
			{
				m_IsOffScreen = true;
				m_BottomLeft.x = m_WindowBoundries.left - m_TextureWidthSnipet;
				if (!m_IsAlive)
					m_IsAlive = true;
				if (m_BottomLeft.y < m_InitialHeight)
				{
					m_BottomLeft.y = m_InitialHeight;
				}
			}
			else
			{
				m_IsOffScreen = false;
			}
		if (m_Velocity.x < 0)
			if (m_CollisionRect.left + m_TextureWidthSnipet < m_WindowBoundries.left)
			{
				m_IsOffScreen = true;
				m_BottomLeft.x = m_WindowBoundries.left + m_WindowBoundries.width + m_TextureWidthSnipet;
				if (!m_IsAlive)
					m_IsAlive = true;
				if (m_BottomLeft.y < m_InitialHeight)
				{
					m_BottomLeft.y = m_InitialHeight;
				}
			}
			else
			{
				m_IsOffScreen = false;
			}
	}
	else 
	{
		m_BottomLeft.x += m_Velocity.x/4 * elapsedSec;
		m_BottomLeft.y += m_Velocity.y * elapsedSec;
	}
}

WalkingEnemy::~WalkingEnemy()
{
	if (m_StalagmiteCreated)
	{
		delete m_pStalagmite;
	}
	delete m_pAnimationAlive;
	delete m_pAnimationDead;
}

void WalkingEnemy::InitializeAnimations()
{
	m_pAnimationAlive = new Animation(m_pEnemiesAlive, static_cast<int>(m_Type), 0, 4, 10, 4, 3);
	m_pAnimationDead = new Animation(m_pEnemiesDead, static_cast<int>(m_Type), 0, 4, 10, 4, 3);
}

void WalkingEnemy::Draw() const
{
	DrawStalagmites();
	glPushMatrix();
	{
		if (m_Velocity.x < 0)
		{
			glTranslatef(m_BottomLeft.x, 0, 0);
			glScalef(-1, 1, 1);
			glTranslatef(-(m_BottomLeft.x), 0, 0);
		}
		if (m_IsAlive)
			m_pAnimationAlive->Draw(m_BottomLeft);
		if(!m_IsAlive)
			m_pAnimationDead->Draw(m_BottomLeft);
	}
	glPopMatrix();
}

void WalkingEnemy::SetMeasures()
{
	float textureWidth = m_pEnemiesAlive->GetWidth();
	float textureHeight = m_pEnemiesAlive->GetHeight();
	float textureWidthSnipet = textureWidth / m_NrColumns;
	float textureHeightSnipet = textureHeight / m_NrRows;

	Rectf birdRectf{};
	birdRectf.left = m_BottomLeft.x;
	birdRectf.bottom = m_BottomLeft.y;
	birdRectf.width = textureWidthSnipet;
	birdRectf.height = textureHeightSnipet;

	NPC::SetMeasures(textureWidth, textureHeight, textureWidthSnipet, textureHeightSnipet, birdRectf);
}

void WalkingEnemy::SetEnemyType()
{
	int rand = std::rand() % 100;

	if(rand % 2 == 0)
		NPC::m_Type = NPC::Type(EnemyType::seal);
	if (rand % 2 != 0)
		NPC::m_Type = NPC::Type(EnemyType::bear);
}

void WalkingEnemy::SetEnemyState(int& state, const Rectf& actorShape)
{
	if (IsOverlapping(m_CollisionRect, m_pPlayer->GetShape()) && (m_pPlayer->GetPlayerState() != int(State::kill)))
		if (m_IsAlive)
			m_pPlayer->SetState(1);
	if (IsOverlapping(m_CollisionRect, actorShape) && (m_pPlayer->GetPlayerState() == int(State::kill)))
	{
		if (m_IsAlive)
		{
			m_pGameLevel->GetSoundManager()->GetSoundEffectPointer("EnemyDead")->Play(0);
		}
		m_IsAlive = false;
	}

	if(m_StalagmiteCreated)
		if (m_pStalagmite->GetOverlap() && (m_pPlayer->GetPlayerState() != int(State::kill)) && (!m_pStalagmite->GetDestroyed()))
			m_pPlayer->SetState(1);
	
	if (m_VelocityXFlipped && !(m_pGameLevel->IsOnGround(m_CollisionRect, m_Velocity)))
		m_IsAlive = false;
}

void WalkingEnemy::InitializeStalagmites()
{
	if (!m_StalagmiteCreated)
	{
			Point2f bottomLeft{};
			if (m_Velocity.x > 0)
			{
				bottomLeft = Point2f{ m_BottomLeft.x + m_TextureWidthSnipet, m_BottomLeft.y };
				m_pStalagmite = new Stalagmite(m_pGameLevel, bottomLeft, m_TextureWidthSnipet);
				m_pStalagmite->SetVelocity(m_Velocity);
			}
			if (m_Velocity.x < 0)
			{
				bottomLeft = Point2f{ m_BottomLeft.x - m_TextureWidthSnipet - 8, m_BottomLeft.y };
				m_pStalagmite = new Stalagmite(m_pGameLevel, bottomLeft, m_TextureWidthSnipet);
				m_pStalagmite->SetVelocity(m_Velocity);
			}
			m_pStalagmite->SetWindowWidth(m_WindowBoundries);
			m_StalagmiteCreated = true;
	}
}

void WalkingEnemy::DrawStalagmites() const
{	
	if(m_HasStalagmite)
		m_pStalagmite->Draw(m_BottomLeft);
}

void WalkingEnemy::UpdateStalagmites(float elapsedSec)
{
	//if (!m_IsAlive)
	//{
	//	//m_HasStalagmite = false;
	//	m_NeedsStalagmite = false;
	//}
	if (m_NeedsStalagmite && !m_StalagmiteCreated)
	{
		if (!m_VelocityXFlipped)
		{
			FlipXVelocity();
		}
		if (m_IsOffScreen)
		{
			m_HasStalagmite = true;
			InitializeStalagmites();
		}
	}
	if (m_StalagmiteCreated)
	{
		if (m_HasStalagmite)
		{
			m_pStalagmite->Update(elapsedSec);
			m_pStalagmite->Overlap(m_ActorShape);
			m_pStalagmite->SetActorState(int(m_ActorState));
			m_TimeToDestroy += elapsedSec;
			if (m_TimeToDestroy > 2)
			{
				if (m_pStalagmite->GetDestroyed())
				{
					delete m_pStalagmite;
					m_pStalagmite = nullptr;
					m_HasStalagmite = false;
					m_StalagmiteCreated = false;
					m_TimeToDestroy = 0;
				}
				m_NeedsStalagmite = false;
				m_VelocityXFlipped = false;
			}
			if (m_IsOffScreen && m_VelocityXFlipped)
			{
				FlipXVelocity();
				m_VelocityXFlipped = false;
				m_pStalagmite->SetVelocity(m_Velocity);
				m_pStalagmite->SetNewBottomLeft(m_BottomLeft);
			}
		}
	}
}

void WalkingEnemy::FlipXVelocity()
{
	if (m_Velocity.x > 0)
	{
		m_Velocity.x = m_HorSpeed * -1;
		m_VelocityXFlipped = true;
		return;
	}
	if (m_Velocity.x < 0)
	{
		m_Velocity.x = m_HorSpeed;
		m_VelocityXFlipped = true;
		return;
	}
}

void WalkingEnemy::UpdateAnimations(float elapsedSec)
{
	m_pAnimationAlive->Update(elapsedSec);
	m_pAnimationDead->Update(elapsedSec);
}

void WalkingEnemy::SetVelocity()
{
	if (m_NrOfEnemy % 2 == 0)
		m_Velocity = Vector2f{ m_HorSpeed , -75 };
	if (m_NrOfEnemy % 2 != 0)
		m_Velocity = Vector2f{ m_HorSpeed * -1, -75 };
	if (m_HasStalagmite)
		m_pStalagmite->SetVelocity(m_Velocity);
}

void WalkingEnemy::UpdateCollisionTools()
{
	if (m_Velocity.x > 0)
	{
		m_CollisionRect = Rectf{ m_BottomLeft.x, m_BottomLeft.y, m_TextureWidthSnipet, m_TextureHeightSnipet };
		Point2f center{ m_CollisionRect.GetCenter() };
		Point2f dot{ m_CollisionRect.GetCenter().x, m_CollisionRect.GetCenter().y - m_TextureHeightSnipet };
		m_LineCollisonDetection = Line2f{ center, dot };
	}
	if (m_Velocity.x < 0)
	{
		m_CollisionRect = Rectf{ m_BottomLeft.x - m_TextureWidthSnipet, m_BottomLeft.y, m_TextureWidthSnipet, m_TextureHeightSnipet };
		Point2f center{ m_CollisionRect.GetCenter() };
		Point2f dot{ m_CollisionRect.GetCenter().x, m_CollisionRect.GetCenter().y - m_TextureHeightSnipet };
		m_LineCollisonDetection = Line2f{ center, dot };
	}
}



