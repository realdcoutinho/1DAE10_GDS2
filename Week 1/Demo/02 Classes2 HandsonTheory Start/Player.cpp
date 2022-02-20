#include "pch.h"
#include "Player.h"
#include <iostream>

int Player::m_NumberOfPlayers{ 0 };


Player::Player(const std::string& name)
	: m_Name{name}
	, m_Score{}
{
	std::cout << m_Name << ": constructor is executing\n";
	++m_NumberOfPlayers;
}

Player::~Player()
{
	std::cout << m_Name << ": destructor is executed\n";
	--m_NumberOfPlayers;
}

void Player::ShowMessage() const
{
	std::string message{ GenerateMessage() };
	std::cout << message << '\n';
}

void Player::SetScore(int newScore)
{
	if (newScore >= 0)
	{
		m_Score = newScore;
	}
}

int Player::GetNumberOfPlayers()
{
	return m_NumberOfPlayers;
}

std::string Player::GenerateMessage() const
{
	std::string message{ "I am " + this->m_Name + " and my score is: " + std::to_string(this->m_Score) };
	return message;
}
