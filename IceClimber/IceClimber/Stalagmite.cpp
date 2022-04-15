#include "pch.h"
#include "Stalagmite.h"
#include <iostream>

Stalagmite::Stalagmite(Point2f bottomLeft, float offSet)
	: Damage(bottomLeft, 2, 2, 0, 0, 2, 0)
	, m_pTextureStalagmite{new Texture("./Images/Stalagmite.png")}
	, m_State{State::form}
	, m_PositionOffSet{offSet}
{
	std::cout << "Stalagmite Created" << '\n';
	SetMeasures();
	SetSourceRect();
}

Stalagmite::~Stalagmite()
{
	delete m_pTextureStalagmite;
}

void Stalagmite::Draw(Point2f bottomLeft) const
{
	Point2f bottomLeftPos{ bottomLeft.x + m_PositionOffSet ,  bottomLeft.y };
	if ((!m_IsOverlapping) && (m_ActorState != ActorState::kill))
	{
		m_pTextureStalagmite->Draw(m_BottomLeft, m_SourceRect);
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
	GameObject::SetMeasures(textureWidth, textureHeight, textureWidthSnipet, textureHeightSnipet, destRect);
}

void Stalagmite::SetSourceRect()
{
	m_SourceRect.left = m_TextureSnipetWidth;
	m_SourceRect.bottom = m_TextureSnipetHeight * int(m_State);
	m_SourceRect.width = m_TextureSnipetWidth;
	m_SourceRect.height = m_TextureSnipetHeight;
}