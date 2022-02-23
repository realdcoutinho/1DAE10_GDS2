#include "pch.h"
#include "Card.h"
#include "Texture.h"
#include <iostream>

int Card::m_NumberOfCards{ 0 };

const int Card::minRank{ 1 };
const int Card::maxRank{ 13 };

Card::Card(Suit suit, int rank, float speed, const Circlef& circle)
	: m_Suit(suit)
	, m_Rank(rank)
	, m_RotSpeed{ speed }
	, m_Circle{circle}
	, m_Angle{ m_NumberOfCards * (360.f/13.f) }
{
	std::string filename{ GetImagePath(suit,rank) };
	m_pTexture = new Texture (filename);
	m_Width = m_pTexture->GetWidth();
	m_Height = m_pTexture->GetHeight();
	++m_NumberOfCards;
	std::cout << "There were initiated " << m_NumberOfCards << " cards" << '\n';
}

Card::~Card()
{
	m_pTexture->~Texture();
	std::cout << "It was deleted the card number: " << m_NumberOfCards << '\n';
	--m_NumberOfCards;
}

void Card::Update(float elapsedSec)
{
	m_Angle += m_RotSpeed * elapsedSec;
	if (m_Angle > 360)
		m_Angle = 0;
}

void Card::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Circle.center.x, m_Circle.center.y, 0);
	glScalef(0.45f, 0.45f, 1.0f);
	glRotatef(m_Angle, 0, 0, 1);
	glTranslatef(-m_Circle.center.x, -m_Circle.center.y, 0);

	m_pTexture->Draw();
	glPopMatrix();
}






float Card::GetWidth() const
{
	return m_Width;
}

float Card::GetHeight() const
{
	return m_Height;
}


std::string Card::GetImagePath(Suit suit, int rank) const
{
	std::string fileType{ ".png" };
	std::string path{ "resources/" };
	int index{ int(suit) * 100 + rank };
	std::string number{ std::to_string(index) };
	
	std::string fullPath{ path + number + fileType };
	return fullPath;
}