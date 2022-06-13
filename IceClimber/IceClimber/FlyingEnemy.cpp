#include "pch.h"
#include "FlyingEnemy.h"
#include "Level.h"
#include <iostream>
using namespace utils;


FlyingEnemy::FlyingEnemy(Player* player, Level* level, Point2f bottomLeft, float windowWidth)
	: NPC(player, level, bottomLeft, windowWidth, 3, 4, 4, 0, 0, 10)
	, m_pEnemiesAlive{level->GetTextureManager()->GetTexturePointer("EnemyAlive")}
	, m_pEnemiesDead{level->GetTextureManager()->GetTexturePointer("EnemyDead")}
	, m_HorSpeed{ 25 }
{
	std::cout << "Enemy Created" << '\n';
	SetMeasures();
	SetEnemyType();
	InitializeAnimation();
}

void FlyingEnemy::InitializeAnimation()
{
	m_pAnimationAlive = new Animation(m_pEnemiesAlive, static_cast<int>(m_Type), 0, 4, 8, 4, 3);
	m_pAnimationDead = new Animation(m_pEnemiesDead, static_cast<int>(m_Type), 0, 4, 8, 4, 3);
}

FlyingEnemy::~FlyingEnemy()
{
}

void FlyingEnemy::Update(float elapsedSec)
{
	if (!m_IsOverlapping)
	{
		UpdateAnimations(elapsedSec);
		//NPC::UpdatePosition(elapsedSec);
	}
}

void FlyingEnemy::UpdateAnimations(float elapsedSec)
{
	m_pAnimationAlive->Update(elapsedSec);
	m_pAnimationDead->Update(elapsedSec);
}

void FlyingEnemy::Draw() const
{
	glPushMatrix();
	{
		if (m_Velocity.x < 0)
		{
			glTranslatef(m_BottomLeft.x, 0, 0);
			glScalef(-1, 1, 1);
			glTranslatef(-(m_BottomLeft.x), 0, 0);
		}
		//FillRect(m_BottomLeft, m_TextureWidthSnipet, m_TextureHeightSnipet);
		if (m_IsAlive)
			m_pAnimationAlive->Draw(m_BottomLeft);
		if (!m_IsAlive)
			m_pAnimationDead->Draw(m_BottomLeft);
	}
	glPopMatrix();
}

void FlyingEnemy::SetMeasures()
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

void FlyingEnemy::SetEnemyType()
{
	NPC::m_Type = NPC::Type(EnemyType::bird);	
}

void FlyingEnemy::SetEnemyState(int& state, const Rectf& actorShape)
{
	m_ActorShape = actorShape;
	m_ActorState = State(state);
	if (IsOverlapping(m_CollisionRect, actorShape) && (m_IsAlive) && (state == int(State::kill)))
	{
		if (m_Type != Type::typeThree)
		{
			m_Velocity.x = -m_Velocity.x;
			m_IsAlive = false;
		}
		if (m_Type == Type::typeThree)
		{
			m_Velocity.x = 0;
			m_IsAlive = false;
		}
	}
	if (IsOverlapping(m_CollisionRect, actorShape) && (m_IsAlive) && (state != int(State::other)))
	{
		state = 2;
	}
}