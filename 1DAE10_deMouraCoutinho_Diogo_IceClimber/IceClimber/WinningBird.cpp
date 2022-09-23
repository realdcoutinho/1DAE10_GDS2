#include "pch.h"
#include "WinningBird.h"
#include "Level.h"
#include <iostream>
using namespace utils;

WinningBird::WinningBird(Player* player, Level* level, Point2f bottomLeft, float windowWidth)
	: NPC(player, level,bottomLeft, windowWidth, 2, 4, 4, 0, 0, 8)
	, m_pTextureBird{level->GetTextureManager()->GetTexturePointer("WinningBird")}
	, m_HorSpeed{50}
	, m_IsOffScreen{false}
{
	SetMeasures();
	SetColorBird();
	InitializeAnimation();
	NPC::SetVelocity(m_HorSpeed);
}

WinningBird::~WinningBird()
{
	delete m_AnimationBird;
}

void WinningBird::InitializeAnimation()
{
	m_AnimationBird = new Animation(m_pTextureBird, static_cast<int>(m_Type), 0, 4, 8, 4, 2);
}

void WinningBird::Draw() const
{
	glPushMatrix();
	{
		if (m_Velocity.x < 0)
		{
			glTranslatef(m_BottomLeft.x, 0, 0);
			glScalef(-1, 1, 1);
			glTranslatef(-(m_BottomLeft.x), 0, 0);
		}
		m_AnimationBird->Draw(m_BottomLeft);
	}
	glPopMatrix();

}

void WinningBird::Update(float elapsedSec)
{
	if (!m_IsOverlapping)
	{
		m_AnimationBird->Update(elapsedSec);
		NPC::Update(elapsedSec);
	}
}

void WinningBird::SetMeasures()
{
	float textureWidth = m_pTextureBird->GetWidth();
	float textureHeight = m_pTextureBird->GetHeight();
	float textureWidthSnipet = textureWidth / m_NrColumns;
	float textureHeightSnipet = textureHeight / m_NrRows;

	Rectf birdRectf{};
	birdRectf.left = m_BottomLeft.x;
	birdRectf.bottom = m_BottomLeft.y;
	birdRectf.width = textureWidthSnipet;
	birdRectf.height = textureHeightSnipet;

	NPC::SetMeasures(textureWidth, textureHeight, textureWidthSnipet, textureHeightSnipet, birdRectf);
}

void WinningBird::SetColorBird()
{
	int rand = std::rand() % 100;

	if (rand % 2 == 0)
		NPC::m_Type = NPC::Type(ColorBird::blue);
	if (rand % 2 != 0)
		NPC::m_Type = NPC::Type(ColorBird::red);
}