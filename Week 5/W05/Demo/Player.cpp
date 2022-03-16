#include "Player.h"
#include <iostream>

Player::Player(const std::string& name, int score)
	: m_Score{score}
	, m_Name{ name }
	, m_Health{}
{

}

void Player::AddScore(int toAdd)
{
	m_Score += toAdd;
}

std::ostream& operator<<(std::ostream& out, const Player& player)
{
	out << "My name is " << player.m_Name << " and my score is " << player.m_Score;
	return out;
}