#include "pch.h"
#include "Bonus.h"
using namespace utils;

Bonus::Bonus(Point2f bottomLeft)
	: m_BottomLeft{bottomLeft}
	, m_NrOfBonus{20}
	, m_IsCaught{false}
	, m_pTextureBonus{new Texture("./Images/BonusVegetables.png")}
{
	SetMeasures();
	SetDestRect();
	GetRandomBonus();
	SetSourceRect();
}

Bonus::~Bonus()
{
	delete m_pTextureBonus;
}

void Bonus::Draw() const
{
	if (!m_IsCaught)
		m_pTextureBonus->Draw(m_BottomLeft, m_SourceRect);
}

void Bonus::SetMeasures()
{
	m_TextureWidth = m_pTextureBonus->GetWidth();
	m_TextureHeight = m_pTextureBonus->GetHeight();
	m_TextureSnipetWidth = m_TextureWidth / m_NrOfBonus;
}

void Bonus::SetDestRect()
{
	m_DestRect.left = m_BottomLeft.x + m_TextureHeight / 4;
	m_DestRect.bottom = m_BottomLeft.y + m_TextureHeight / 4;
	m_DestRect.width = m_TextureSnipetWidth - m_TextureHeight / 2;
	m_DestRect.height = m_TextureHeight - m_TextureHeight / 2;
}

int Bonus::GetRandomBonus()
{
	int bonus = std::rand() % 20;
	return bonus;
}

void Bonus::SetSourceRect()
{
	m_SourceRect.left = m_TextureSnipetWidth * float(GetRandomBonus());
	m_SourceRect.bottom = 0;
	m_SourceRect.width = m_TextureSnipetWidth ;
	m_SourceRect.height = m_TextureHeight;
}

void Bonus::Overlap(const Rectf& actorShape)
{
	if (IsOverlapping(actorShape, m_DestRect))
		m_IsCaught = true;
}