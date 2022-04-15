#include "pch.h"
#include "WinningBird.h"
#include <iostream>
using namespace utils;

WinningBird::WinningBird(Point2f bottomLeft, float windowWidth)
	: NPC(bottomLeft, windowWidth, 2, 4, 4, 0, 0, 8)
	, m_pTextureBird{new Texture("./Images/WinningBird.png")}
	, m_HorSpeed{50}
{
	std::cout << "Winning Bird Created" << '\n';
	SetMeasures();
	SetColorBird();
	NPC::SetVelocity(m_HorSpeed);
}

WinningBird::~WinningBird()
{
	delete m_pTextureBird;
}

void WinningBird::Draw(Texture* textureOne) const
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
		textureOne->Draw(m_BottomLeft, NPC::GetSourceRect());
	}
	glPopMatrix();
}

void WinningBird::Update(float elapsedSec)
{
	if (!m_IsOverlapping)
	{
		NPC::UpdateFrames(elapsedSec);
		NPC::UpdatePosition(elapsedSec);
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