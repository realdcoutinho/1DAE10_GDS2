#include "pch.h"
#include "Stalagtites.h"
#include <iostream>
#include "Level.h"
using namespace utils;

Stalagtites::Stalagtites(Level* level, Point2f bottomLeft)
	: Damage(bottomLeft, 0, 2, 5, 0, 0, 2, 0)
	, m_pTextureStalatites{ level->GetTextureManager()->GetTexturePointer("Stalagtites") }
	, m_IsDestroyed{ false }
	, m_FormingTime{ 5 }
	, m_CurrentTime{0}
	, m_State{State::forming}
	, m_OriginalBL{}
	, m_pLevel{ level }
{
	SetMeasures();
	InitializeAnimations();
}

Stalagtites::~Stalagtites()
{
	delete m_pAnimationStalateiteForming;
	delete m_pAnimationStalagmiteFalling;
}

void Stalagtites::Draw(Point2f bottomLeft) const
{
	if (m_CurrentTime >= 0)
	{
		switch (m_State)
		{
		case(State::forming):
			m_pAnimationStalagmiteFalling->Draw(m_BottomLeft);
			break;
		case(State::falling):
			m_pAnimationStalateiteForming->Draw(m_BottomLeft);
			break;
		}
	}
}

void Stalagtites::Update(float elapsedSec)
{
	UpdateState(elapsedSec);
	Damage::Update(elapsedSec);
	if (m_CurrentTime >= 0)
	{
		m_pAnimationStalateiteForming->Update(elapsedSec);
		m_pAnimationStalagmiteFalling->Update(elapsedSec);
	}
	m_DestRect = Rectf{ m_BottomLeft.x, m_BottomLeft.y, m_TextureSnipetWidth, m_TextureSnipetHeight };
}

void Stalagtites::UpdateState(float elapsedSec)
{
	m_CurrentTime += elapsedSec;
	if (m_CurrentTime >= m_FormingTime && m_CurrentTime <= (m_FormingTime + 0.05f))
	{
		m_pLevel->GetSoundManager()->GetSoundEffectPointer("Falling_Stalagtite")->Play(0);
	}
	if (m_CurrentTime >= m_FormingTime)
	{
		m_State = State::falling;
		m_Velocity.y = -200;
	}
	if (m_CurrentTime < m_FormingTime)
	{
		m_State = State::forming;
	}
	if (m_BottomLeft.y + m_TextureSnipetHeight <= 0)
	{
		m_Velocity.y = 0;
		m_BottomLeft = m_OriginalBL;
		m_State = State::forming;
		m_CurrentTime = float(-30 + (std::rand() % (-10 - -30 + 1)));
	}
	if (m_IsOverlapping && (m_State == State::falling))
	{
		m_CurrentTime = float(-30 + (std::rand() % (-10 - -30 + 1)));
		m_State = State::forming;
		m_BottomLeft = m_OriginalBL;
		m_Velocity.y = 0;
	}
	if (m_IsOverlapping && (m_ActorState == ActorState::jump) && (m_CurrentTime >= 0.0f))
	{
		m_CurrentTime = float(-30 + (std::rand() % (-10 - -30 + 1)));
		m_State = State::forming;
		m_BottomLeft = m_OriginalBL;
		m_Velocity.y = 0;
	}
	m_IsOverlapping = false;
}


void Stalagtites::InitializeAnimations()
{
	m_pAnimationStalateiteForming = new Animation(m_pTextureStalatites, static_cast<int>(State::forming), 0, 5, 5, 5, 2);
	m_pAnimationStalagmiteFalling = new Animation(m_pTextureStalatites, static_cast<int>(State::falling), 0, 5, 1, 5, 2);
}

void Stalagtites::SetMeasures()
{
	float textureWidth = m_pTextureStalatites->GetWidth();
	float textureHeight = m_pTextureStalatites->GetHeight();
	float textureWidthSnipet = textureWidth / m_NrColumns;
	float textureHeightSnipet = textureHeight / m_NrRows;
	Rectf destRect;
	destRect.left = m_BottomLeft.x + textureWidthSnipet / 4;
	destRect.bottom = m_BottomLeft.y + textureWidthSnipet / 4;
	destRect.width = textureWidthSnipet - textureWidthSnipet / 2;
	destRect.height = textureHeightSnipet - textureHeightSnipet / 2;
	m_DestRect = destRect;
	m_BottomLeft = Point2f{ m_BottomLeft.x, m_BottomLeft.y - textureHeightSnipet };
	m_OriginalBL = m_BottomLeft;
	m_CurrentTime = float(-20 + (std::rand() % (-5 - -20 + 1))); // rnadom values to randomize initial time
	GameObject::SetMeasures(textureWidth, textureHeight, textureWidthSnipet, textureHeightSnipet, destRect);
}

bool Stalagtites::GetOverlap() const
{
	if ((m_State == State::falling))
		return m_IsOverlapping;
	else
		return false;
}

bool Stalagtites::GetDestroyed() const
{
	return m_IsDestroyed;
}

