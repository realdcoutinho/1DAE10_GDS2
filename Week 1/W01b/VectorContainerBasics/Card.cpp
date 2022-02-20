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
}

Card::~Card()
{
	m_pTexture->~Texture();
}

void Card::Draw(const Rectf& destRect)
{
	std::string fullPath{ GetImagePath(Suit(m_Suit), m_Rank) };
	m_pTexture->Draw(destRect);
}

float Card::GetWidth()
{
	float width{ m_pTexture->GetWidth() };
	return width;
}

float Card::GetHeight()
{
	float height{ m_pTexture->GetHeight() };
	return height;
}

std::string Card::GetImagePath(Suit suit, int rank)
{
	std::string fileType{ ".png" };
	std::string path{ "resource" };
	int index{ int(suit) * 100 + rank };
	std::string number{ std::to_string(index) };
	
	std::string fullPath{ path + number + fileType };
	return fullPath;
}