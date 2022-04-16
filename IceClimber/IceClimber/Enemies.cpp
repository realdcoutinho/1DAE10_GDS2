#include "pch.h"
#include "Enemies.h"
#include <iostream>
using namespace utils;

Enemies::Enemies(Point2f bottomLeft, float windowWidth, float widthText, float heightText)
	: NPC(bottomLeft, windowWidth, 3, 4, 4, 0, 0, 10)
	, m_TextureWidthTemp{ widthText }
	, m_TextureHeightTemp{ heightText }
	, m_HorSpeed{ 25 }

{
	std::cout << "Enemy Created" << '\n';
	SetMeasures();
	SetEnemyType();
	NPC::SetVelocity(m_HorSpeed);


	InitializeStalagmites();
	SetVelocity();
	
}

Enemies::~Enemies()
{
	delete m_pStalagmite;
}

void Enemies::Update(float elapsedSec)
{
	if (!m_IsOverlapping)
	{
		NPC::UpdateFrames(elapsedSec);
		NPC::UpdatePosition(elapsedSec);
	}
	UpdateStalagmites(elapsedSec);
}


void Enemies::Draw(Texture* textureOne, Texture* textureTwo) const
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

		//DrawStalagmites();
		if (m_IsAlive)
			//m_pTextureEnemyAlive->Draw(m_BottomLeft, NPC::GetSourceRect());
			textureOne->Draw(m_BottomLeft, NPC::GetSourceRect());
	
		if(!m_IsAlive)
			textureTwo->Draw(m_BottomLeft, NPC::GetSourceRect());
	}
	glPopMatrix();
}

void Enemies::SetMeasures()
{
	float textureWidth = m_TextureWidthTemp;
	float textureHeight = m_TextureHeightTemp;
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
	//if (rand <= 33)
	//
	//if (rand >= 33 && rand <= 66)
	//if (rand >= 66 && rand <= 100)
	//	NPC::m_Type = NPC::Type(EnemyType::bird);
}

void Enemies::SetEnemyState(int& state, const Rectf& actorShape)
{
	m_ActorShape = actorShape;
	m_ActorState = State(state);
	if (IsOverlapping(m_DestRect, actorShape) && (m_IsAlive) && (state == int(State::kill)))
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
	if (IsOverlapping(m_DestRect, actorShape) && (m_IsAlive) && (state != int(State::other)))
	{
		state = 2;
	}
}

void Enemies::InitializeStalagmites()
{
	Point2f bottomLeft{};
	if (m_Velocity.x > 0)
	{
		bottomLeft = Point2f{ m_BottomLeft.x + m_TextureWidthSnipet, m_BottomLeft.y };
		m_pStalagmite = new Stalagmite(bottomLeft, m_TextureWidthSnipet);
	}
	if (m_Velocity.x < 0)
	{
		bottomLeft = Point2f{ m_BottomLeft.x - m_TextureWidthSnipet - 8, m_BottomLeft.y };
		m_pStalagmite = new Stalagmite(bottomLeft, m_TextureWidthSnipet);
	}
	m_pStalagmite->SetWindowWidth(m_WindowWidth);


	//bottomLeft = Point2f{ m_BottomLeft.x + m_TextureWidthSnipet, m_BottomLeft.y };
	
}

void Enemies::DrawStalagmites() const
{
	m_pStalagmite->Draw(m_BottomLeft);
	//textureOne->Draw(m_BottomLeft);
}

void Enemies::UpdateStalagmites(float elapsedSec)
{
	m_pStalagmite->Update(elapsedSec);
	m_pStalagmite->Overlap(m_ActorShape);
	m_pStalagmite->SetActorState(int(m_ActorState));
}

void Enemies::SetVelocity()
{
	m_pStalagmite->SetVelocity(m_Velocity);
}