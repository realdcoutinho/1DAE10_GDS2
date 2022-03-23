// DemoStackVsHeap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class Player
{
public:
	Player()
	{
		std::cout << "class Player: adress of m_Health: " << &m_Health << '\n';
	}
private:
	int m_Health{ 10 };
	int m_Numbers[10]{};
};

class Game
{
public:
	Game()
	{
		std::cout << "class Game, address of me: " << this << '\n';
	}
private:
	int m_Number{};
	Player m_Player{};
};

int main()
{
	int i{};
	std::cout << "In Main Address of i: " << &i << '\n';
	std::cout << "Game instance on the stack" << '\n';
	Game game{}; //Game and m_Player and m_Numbers on stack
	std::cout << '\n' << '\n' << '\n';
	std::cout << "Game instance on the heap" << '\n';
	Game* pGame{ new Game{} }; // Game and m_Player and m_Numbers on heap
	delete pGame;
}

