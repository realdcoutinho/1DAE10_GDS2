#pragma once
#include <string>
class Player
{
public:
	Player(const std::string& name);
	~Player();
	void ShowMessage();
	void SetScore(int newScore);
private:
	std::string GenerateMessage();
	std::string m_Name;
	int m_Score;
};
