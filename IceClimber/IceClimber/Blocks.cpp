#include "pch.h"
#include "Blocks.h"
#include <iostream>
using namespace utils;

Blocks::Blocks(Point2f bottomLeft, int type, float tempWidth, float tempHeight)
	: Platform{ bottomLeft, 3, 1, type }
	, m_TextureWidthTemp{ tempWidth }
	, m_TextureHeightTemp{ tempHeight }

{
	SetMeasures();
	Platform::SetCollision();
	
}

Blocks::~Blocks()
{
	//delete m_pBlocks;
}

void Blocks::SetMeasures()
{
	m_TextureWidth = m_TextureWidthTemp;
	m_TextureHeight = m_TextureHeightTemp;
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

void Blocks::Draw(Texture* textureOne) const
{
	if (!m_IsDestroyed) //if no destroyed, fraw
		textureOne->Draw(m_BottomLeft, m_SourceRect);
}

float Blocks::GetWidth() const
{
	return m_TextureSnipetWidth;
}
float Blocks::GetHeight() const
{
	return m_TextureSnipetHeight;
}



