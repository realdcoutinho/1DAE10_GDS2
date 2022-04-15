#include "pch.h"
#include "Bonus.h"
#include <iostream>
using namespace utils;

Bonus::Bonus(Point2f bottomLeft, float width, float height)
	: GameObject(bottomLeft, 1, 20)
	, m_NrOfBonus{20}
	//, m_pTextureBonus{new Texture("./Images/BonusVegetables.png")}
	, m_WidthTemp{width}
	, m_HeightTemp{height}
{
	SetMeasures();
	SetSourceRect();
}

Bonus::~Bonus()
{
	//delete m_pTextureBonus;
}

void Bonus::Draw(Texture* textureOne) const
{
	if (!m_IsOverlapping)
		textureOne->Draw(m_BottomLeft, m_SourceRect);
	std::cout << "Is Drawing" << '\n';
}

void Bonus::SetMeasures()
{
	//float textureWidth = m_pTextureBonus->GetWidth();
	//float textureHeight = m_pTextureBonus->GetHeight();

	float textureWidth = m_WidthTemp;
	float textureHeight = m_HeightTemp;

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