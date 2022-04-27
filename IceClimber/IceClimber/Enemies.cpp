#include "pch.h"
#include "Enemies.h"
#include "Level.h"
#include "Player.h"
#include <iostream>
using namespace utils;

Enemies::Enemies(Player* player,Level* level, Point2f bottomLeft, float windowWidth)
	: NPC(bottomLeft, windowWidth, 3, 4, 4, 0, 0, 10)
	, m_pEnemiesAlive{level->GetTextureManager()->GetTexturePointer("EnemyAlive")}
	, m_pEnemiesDead{level->GetTextureManager()->GetTexturePointer("EnemyDead")}
	, m_pPlayer{ player }
	, m_HorSpeed{ 25 }
	, m_pGameLevel{level}
{
	SetMeasures();
	SetEnemyType();
	InitializeAnimations();
	NPC::SetVelocity(m_HorSpeed);
	InitializeStalagmites();
	SetVelocity();
}

Enemies::~Enemies()
{
	delete m_pStalagmite;
	delete m_pAnimationAlive;
	delete m_pAnimationDead;
}

void Enemies::InitializeAnimations()
{
	m_pAnimationAlive = new Animation(m_pEnemiesAlive, static_cast<int>(m_Type), 0, 4, 10, 4, 3);
	m_pAnimationDead = new Animation(m_pEnemiesDead, static_cast<int>(m_Type), 0, 4, 10, 4, 3);
}


void Enemies::Update(float elapsedSec)
{
	m_ActorShape = m_pPlayer->GetShape();
	m_ActorState = State(m_pPlayer->GetPlayerState());
	if (!m_IsOverlapping)
	{
		UpdateAnimations(elapsedSec);
		NPC::UpdatePosition(elapsedSec);
	}
	UpdateStalagmites(elapsedSec);
}


void Enemies::Draw() const
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
		//FillRect(m_BottomLeft, m_TextureWidthSnipet, m_TextureHeightSnipet);
		//FillRect(m_DestRect);
		//FillRect(m_pPlayer->GetShape());
		if (m_IsAlive)
			m_pAnimationAlive->Draw(m_BottomLeft);
		if(!m_IsAlive)
			m_pAnimationDead->Draw(m_BottomLeft);
	}
	glPopMatrix();
	
}

void Enemies::SetMeasures()
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

void Enemies::SetEnemyType()
{
	int rand = std::rand() % 100;

	if(rand % 2 == 0)
		NPC::m_Type = NPC::Type(EnemyType::seal);
	if (rand % 2 != 0)
		NPC::m_Type = NPC::Type(EnemyType::bear);
}

void Enemies::SetEnemyState(int& state, const Rectf& actorShape)
{
	if (IsOverlapping(m_DestRect, actorShape) && (m_pPlayer->GetPlayerState() != int(State::kill)))
		if(m_IsAlive)
			m_pPlayer->SetState(1);
	if (IsOverlapping(m_DestRect, actorShape) && (m_pPlayer->GetPlayerState() == int(State::kill)))
		m_IsAlive = false;
}

void Enemies::InitializeStalagmites()
{
	Point2f bottomLeft{};
	if (m_Velocity.x > 0)
	{
		bottomLeft = Point2f{ m_BottomLeft.x + m_TextureWidthSnipet, m_BottomLeft.y };
		m_pStalagmite = new Stalagmite(m_pGameLevel, bottomLeft, m_TextureWidthSnipet);
	}
	if (m_Velocity.x < 0)
	{
		bottomLeft = Point2f{ m_BottomLeft.x - m_TextureWidthSnipet - 8, m_BottomLeft.y };
		m_pStalagmite = new Stalagmite(m_pGameLevel, bottomLeft, m_TextureWidthSnipet);
	}
	m_pStalagmite->SetWindowWidth(m_WindowWidth);
}

void Enemies::DrawStalagmites() const
{
	m_pStalagmite->Draw(m_BottomLeft);
}

void Enemies::UpdateStalagmites(float elapsedSec)
{
	m_pStalagmite->Update(elapsedSec);
	m_pStalagmite->Overlap(m_ActorShape);
	m_pStalagmite->SetActorState(int(m_ActorState));
}

void Enemies::UpdateAnimations(float elapsedSec)
{
	m_pAnimationAlive->Update(elapsedSec);
	m_pAnimationDead->Update(elapsedSec);
}

void Enemies::SetVelocity()
{
	m_pStalagmite->SetVelocity(m_Velocity);
}