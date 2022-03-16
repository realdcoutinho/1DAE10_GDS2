#pragma once
#include <string>

class Player
{
public:
	Player(const std::string& name, int score = 0);
	void AddScore(int toAdd);
	friend std::ostream& operator<<(std::ostream& out, const Player& player);
private:
	std::string m_Name;
	int m_Score, m_Health;
};


std::ostream& operator<<(std::ostream& out, const Player& player);
//std::ostream operator<<(std::ostream& out, const Player& player);

