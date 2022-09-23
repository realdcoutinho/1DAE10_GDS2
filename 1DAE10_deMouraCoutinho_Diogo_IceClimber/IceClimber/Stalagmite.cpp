#include "pch.h"
#include "Stalagmite.h"
#include <iostream>
#include "Level.h"
using namespace utils;

Stalagmite::Stalagmite(Level* level, Point2f bottomLeft, float offSet)
	: Damage(bottomLeft,1, 2, 2, 0, 0, 2, 0)
	, m_pLevel{ level }
	, m_pTextureStalagmite{level->GetTextureManager()->GetTexturePointer("Stalagmite")}
	, m_State{State::form}
	, m_PositionOffSet{offSet}
	, m_IsDestroyed{false}
	, m_Time{0}
	, m_OffSet{100.0f}
{
	SetMeasures();
	InitializeAnimations();
}

Stalagmite::~Stalagmite()
{
	delete m_pAnimationStalagmiteForm;
	delete m_pAnimationStalagmiteDestroyed;
}

void Stalagmite::Draw(Point2f bottomLeft) const
{
		switch (m_State)
		{
		case(State::form):
			if (!m_IsDestroyed)
				m_pAnimationStalagmiteForm->Draw(m_BottomLeft);
			break;
		case(State::destroyed):
			if (m_Time < 2)
				m_pAnimationStalagmiteDestroyed->Draw(m_BottomLeft);
			break;
		case(State::used):
			if (m_Time < 2)
				m_pAnimationStalagmiteDestroyed->Draw(m_BottomLeft);
			break;
		}
}

void Stalagmite::Update(float elapsedSec)
{
	UpdateState(elapsedSec);
	Damage::Update(elapsedSec);
	m_pAnimationStalagmiteForm->Update(elapsedSec);
	if (m_IsDestroyed)
		m_pAnimationStalagmiteDestroyed->Update(elapsedSec);
	FixMapBlock();
}

void Stalagmite::SetNewBottomLeft(Point2f bottomLeft)
{
	if (m_Velocity.x < 0)
	{
		m_BottomLeft = Point2f{ m_OffSet + m_WindowWidth - m_PositionOffSet / 2,  bottomLeft.y };
	}
	if (m_Velocity.x > 0)
	{
		m_BottomLeft = Point2f{ bottomLeft.x ,  bottomLeft.y };
	}
}

void Stalagmite::FixMapBlock()
{
	if (!(m_pLevel->IsOnGround(m_DestRect, m_Velocity)))
	{
		m_State = State::used;
		int index = m_pLevel->GetBlockIndex(m_DestRect, m_Velocity);
		m_pLevel->SetBlockFixed(index);
		m_IsDestroyed = true;
	}
}

void Stalagmite::UpdateState(float elapsedSec)
{
	if (m_IsOverlapping)
		if ((m_ActorState == ActorState::kill))
		{
			m_IsDestroyed = true;
			m_State = State::destroyed;

		}
	if (m_IsDestroyed)
	{
		m_Time += elapsedSec;
		m_Velocity.x = 0;
	}
}

void Stalagmite::SetMeasures()
{
	float textureWidth = m_pTextureStalagmite->GetWidth();
	float textureHeight = m_pTextureStalagmite->GetHeight();
	float textureWidthSnipet = textureWidth / m_NrColumns;
	float textureHeightSnipet = textureHeight / m_NrRows;
	Rectf destRect;
	destRect.left = m_BottomLeft.x + textureWidthSnipet / 4;
	destRect.bottom = m_BottomLeft.y + textureWidthSnipet / 4;
	destRect.width = textureWidthSnipet - textureWidthSnipet / 2;
	destRect.height = textureHeightSnipet - textureHeightSnipet / 2;
	m_DestRect = destRect;
	GameObject::SetMeasures(textureWidth, textureHeight, textureWidthSnipet, textureHeightSnipet, destRect);
}

void Stalagmite::InitializeAnimations()
{
	m_pAnimationStalagmiteForm = new Animation(m_pTextureStalagmite, static_cast<int>(State::form), 0, 2, 1, 2, 2);
	m_pAnimationStalagmiteDestroyed = new Animation(m_pTextureStalagmite, static_cast<int>(State::destroyed), 0, 2, 1, 2, 2);
}

bool Stalagmite::GetOverlap() const
{
	return m_IsOverlapping;
}

bool Stalagmite::GetDestroyed() const
{
	return m_IsDestroyed;
}