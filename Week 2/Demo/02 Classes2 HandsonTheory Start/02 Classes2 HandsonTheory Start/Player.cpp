#include "pch.h"
#include "Player.h"
#include <iostream>

Player::Player(const std::string& name)
	: m_Name{name}
	, m_Score{}
{
	std::cout << m_Name << ": constructor is executing\n";
}

Player::~Player()
{
	std::cout << m_Name << ": destructor is executed\n";
}

void Player::ShowMessage()
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

std::string Player::GenerateMessage()
{
	std::string message{ "I am " + m_Name + " and my score is: " + std::to_string(m_Score) };
	return message;
}
