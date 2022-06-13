#include "pch.h"
#include "Bonus.h"
#include "Level.h"
#include "Texture.h"
#include <iostream>
using namespace utils;

Bonus::Bonus(Level* level, Point2f bottomLeft)
	: GameObject(bottomLeft, 1, 20)
	, m_NrOfBonus{20}
	, m_pLevel{ level }
{
	m_pTextureBonus = m_pLevel->GetTextureManager()->GetTexturePointer("Bonus");
	SetMeasures();
	SetSourceRect();

}

Bonus::~Bonus()
{
}

void Bonus::Draw() const
{
	if (!m_IsOverlapping)
		m_pTextureBonus->Draw(m_BottomLeft, m_SourceRect);
}

void Bonus::SetMeasures()
{
	float textureWidth = m_pTextureBonus->GetWidth();
	float textureHeight = m_pTextureBonus->GetHeight();
	float textureWidthSnipet = textureWidth / m_NrColumns;
	float textureHeightSnipet = textureHeight / m_NrRows;
	Rectf destRect;
	destRect.left = m_BottomLeft.x + textureWidthSnipet / 4;
	destRect.bottom = m_BottomLeft.y + textureWidthSnipet / 4;
	destRect.width = textureWidthSnipet - textureWidthSnipet / 2;
	destRect.height = textureHeightSnipet - textureHeightSnipet / 2;
	GameObject::SetMeasures(textureWidth, textureHeight, textureWidthSnipet, textureHeightSnipet, destRect);
}

void Bonus::SetSourceRect()
{
	m_SourceRect.left = m_TextureSnipetWidth * GetRandomNumber(0, m_NrOfBonus);
	m_SourceRect.bottom = 0;
	m_SourceRect.width = m_TextureSnipetWidth ;
	m_SourceRect.height = m_TextureSnipetHeight;
}