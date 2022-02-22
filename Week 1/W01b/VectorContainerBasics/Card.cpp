#include "pch.h"
#include "Card.h"
#include "Texture.h"
#include <iostream>

const int Card::minRank{ 1 };
const int Card::maxRank{ 13 };

Card::Card(Suit suit, int rank)
	: m_Suit(suit)
	, m_Rank(rank)
{
	std::string filename{ GetImagePath(suit,rank) };
	m_pTexture = new Texture (filename);
	m_Width = m_pTexture->GetWidth();
	m_Height = m_pTexture->GetHeight();
}

Card::~Card()
{
	m_pTexture->~Texture();
}

void Card::Draw(const Rectf& destRect) const
{
	m_pTexture->Draw(destRect);
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