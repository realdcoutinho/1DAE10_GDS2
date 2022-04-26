#include "pch.h"
#include "Stalagmite.h"
#include <iostream>
#include "Level.h"
using namespace utils;

Stalagmite::Stalagmite(Level* level, Point2f bottomLeft, float offSet)
	: Damage(bottomLeft, 2, 2, 0, 0, 2, 0)
	, m_pTextureStalagmite{level->GetTextureManager()->GetTexturePointer("Stalagmite")}
	, m_State{State::form}
	, m_PositionOffSet{offSet}
	, m_IsDestroyed{false}
	, m_Time{0}
{
	SetMeasures();
	InitializeAnimations();
}

Stalagmite::~Stalagmite()
{
	delete m_pAnimationStalagmiteForm;
	delete m_pAnimationStalagmiteDestroyed;
}

void Stalagmite::InitializeAnimations()
{
	m_pAnimationStalagmiteForm = new Animation(m_pTextureStalagmite, static_cast<int>(State::form), 0, 2, 1, 2, 2);
	m_pAnimationStalagmiteDestroyed = new Animation(m_pTextureStalagmite, static_cast<int>(State::destroyed), 0, 2, 1, 2, 2);
}

void Stalagmite::Draw(Point2f bottomLeft) const
{
	Point2f bottomLeftPos{ bottomLeft.x + m_PositionOffSet ,  bottomLeft.y };
	if (m_Time < 2)
	{
		if (!m_IsDestroyed)
			m_pAnimationStalagmiteForm->Draw(m_BottomLeft);
		if (m_IsDestroyed)
				m_pAnimationStalagmiteDestroyed->Draw(m_BottomLeft);
	}
}

void Stalagmite::Update(float elapsedSec)
{
	UpdateState(elapsedSec);
	Damage::Update(elapsedSec);
	m_pAnimationStalagmiteForm->Update(elapsedSec);
	if (m_IsDestroyed)
		m_pAnimationStalagmiteDestroyed->Update(elapsedSec);
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

void Stalagmite::UpdateState(float elapsedSec)
{
	if ((m_ActorState == ActorState::kill))
	{
		std::cout << "kill";
	}

	if (m_IsOverlapping)
		if ((m_ActorState == ActorState::kill))
			m_IsDestroyed = true;
	if (m_IsDestroyed)
	{
		m_Time += elapsedSec;
	}
}