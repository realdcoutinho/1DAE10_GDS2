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
	, m_pBlocks{ level->GetTextureManager()->GetTexturePointer("Block") }
	, m_HasStalagtites{}
	, m_State{State::fixed}

{
	SetMeasures();
	Platform::SetCollision();
	SetStalagtite();
}

Blocks::~Blocks()
{
	if (m_HasStalagtites)
	{
		delete m_pStalagtites;
	}
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
	if (m_IsDestroyed)
	{
		//	m_pLevel->GetSoundManager()->GetSoundEffectPointer("Destroyed")->Play(0);
	}
}

void Blocks::FixedBlocked()
{
	if (m_IsDestroyed)
	{
		m_pLevel->GetSoundManager()->GetSoundEffectPointer("Block_Fixed")->Play(0);
		m_IsDestroyed = false;
		m_DestRect = Rectf{ m_BottomLeft.x, m_BottomLeft.y, m_TextureSnipetWidth, m_TextureSnipetHeight };
		Platform::SetCollision();
	}
}

void Blocks::SetMeasures()
{
	m_TextureWidth = m_pBlocks->GetWidth();
	m_TextureHeight = m_pBlocks->GetHeight();
	m_TextureSnipetWidth = m_TextureWidth / m_NrColumns;
	m_TextureSnipetHeight = m_TextureHeight / m_NrRows;
	m_TotalWidth = m_TextureSnipetWidth * m_NrLenght;
	m_DestRect = Rectf{ m_BottomLeft.x, m_BottomLeft.y, m_TextureSnipetWidth, m_TextureSnipetHeight };
	m_SourceRect.left = 0; //the .left will be dependent on the type
	m_SourceRect.bottom = m_TextureSnipetHeight * -int(m_Type);
	m_SourceRect.width = m_TextureSnipetWidth;
	m_SourceRect.height = m_TextureSnipetHeight;
}

void Blocks::SetStalagtite()
{
	int rand = std::rand() % 100;

	switch (m_Type)
	{
	case(Type::typeOne):
		//if it is the lower type blockn it wont have a stalgamite
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

float Blocks::GetWidth() const
{
	return m_TextureSnipetWidth;
}
float Blocks::GetHeight() const
{
	return m_TextureSnipetHeight;
}

