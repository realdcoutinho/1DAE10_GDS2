#include "pch.h"
#include "Blocks.h"
#include "Level.h"
#include <iostream>
using namespace utils;

Blocks::Blocks(Level* level, Point2f bottomLeft, int type)
	: Platform{ bottomLeft, 3, 1, type }
	, m_pLevel{level}
{
	m_pBlocks = m_pLevel->GetTextureManager()->GetTexturePointer("Block");
	SetMeasures();
	Platform::SetCollision();
	
}

Blocks::~Blocks()
{
	//delete m_pBlocks;
}

void Blocks::SetMeasures()
{
	m_TextureWidth = m_pBlocks->GetWidth();
	m_TextureHeight = m_pBlocks->GetHeight();
	m_TextureSnipetWidth = m_TextureWidth / m_NrColumns;
	m_TextureSnipetHeight = m_TextureHeight / m_NrRows;
	m_TextureSnipetHeight =8;
	m_TotalWidth = m_TextureSnipetWidth * m_NrLenght;
	//
	m_DestRect = Rectf{ m_BottomLeft.x, m_BottomLeft.y, m_TextureSnipetWidth, m_TextureSnipetHeight };
	//
	m_SourceRect.left = 0; //the .left will be dependent on the type
	m_SourceRect.bottom = m_TextureSnipetHeight * -int(m_Type);
	m_SourceRect.width = m_TextureSnipetWidth;
	m_SourceRect.height = m_TextureSnipetHeight;
	//

}

void Blocks::Draw() const
{
	if (!m_IsDestroyed) //if no destroyed, fraw
		m_pBlocks->Draw(m_BottomLeft, m_SourceRect);
}

float Blocks::GetWidth() const
{
	return m_TextureSnipetWidth;
}
float Blocks::GetHeight() const
{
	return m_TextureSnipetHeight;
}



