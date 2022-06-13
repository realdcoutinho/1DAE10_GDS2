#include "pch.h"
#include "Blocks.h"
#include "Level.h"
#include "Stalagtites.h"
#include "Player.h"
#include <iostream>
using namespace utils;

Blocks::Blocks(Level* level, Point2f bottomLeft, int type)
	: Platform{ bottomLeft, 3, 1, type }
	, m_pLevel{level}
	, m_HasStalagtites{}
	, m_State{State::fixed}
{
	m_pBlocks = m_pLevel->GetTextureManager()->GetTexturePointer("Block");
	

	SetMeasures();
	Platform::SetCollision();
	SetStalagmite();
}

void Blocks::SetStalagmite()
{
	int rand = std::rand() % 100;

	switch (m_Type)
	{
	case(Type::typeOne):
			//if (rand > 39 && rand < 47) //simple random values
			//	{
			//		m_pStalagtites = new Stalagtites(m_pLevel, m_BottomLeft);
			//		m_HasStalagtites = true;
			//	}
		break;
		case(Type::typeTwo):
			if (rand > 15 && rand < 25) //simple random values with a larger interval
			{
				m_pStalagtites = new Stalagtites(m_pLevel, m_BottomLeft);
				m_HasStalagtites = true;
			}
		break;
		case(Type::typeThree):
			if (rand > 74 && rand < 85) //simple random values with a even larger interval
			{
				m_pStalagtites = new Stalagtites(m_pLevel, m_BottomLeft);
				m_HasStalagtites = true;
			}
			break;
	}
}

Blocks::~Blocks()
{
	if (m_HasStalagtites)
	{
		delete m_pStalagtites;
	}
}

void Blocks::Update(float elapsedSec)
{
	if (m_HasStalagtites)
	{
		m_pStalagtites->Update(elapsedSec);
		m_pStalagtites->Overlap(m_pLevel->GetActorShape());
		if (m_pStalagtites->GetOverlap())
		{
			m_pLevel->GetPlayerPointer()->SetState(1); //kill satte
		}
	}
	
}

void Blocks::SetMeasures()
{
	m_TextureWidth = m_pBlocks->GetWidth();
	m_TextureHeight = m_pBlocks->GetHeight();
	m_TextureSnipetWidth = m_TextureWidth / m_NrColumns;
	m_TextureSnipetHeight = m_TextureHeight / m_NrRows;
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
	{
		m_pBlocks->Draw(m_BottomLeft, m_SourceRect); //texture
		if (m_HasStalagtites)
		{
			m_pStalagtites->Draw(m_BottomLeft);
		}
	}	
	if(m_IsDestroyed)
	{
		//std::cout << "Hello";
	}
}

float Blocks::GetWidth() const
{
	return m_TextureSnipetWidth;
}
float Blocks::GetHeight() const
{
	return m_TextureSnipetHeight;
}

void Blocks::FixedBlocked()
{
	if (m_IsDestroyed)
	{
		m_IsDestroyed = false;
		m_DestRect = Rectf{ m_BottomLeft.x, m_BottomLeft.y, m_TextureSnipetWidth, m_TextureSnipetHeight };
		Platform::SetCollision();
	}
}



