// 07Classes1HandsonTheory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Player.h"

void Function(Player* pPlayer); 
void ShowStatus();

int main()
{
    std::cout << "Hello World!\n";
	ShowStatus();
	

	// object is on the heap, the pointer is on the stack!!
	Player* pHeapPlayer{ new Player{ "Mr Heap" } };
	ShowStatus();

	pHeapPlayer->SetScore(20);
	pHeapPlayer->ShowMessage();
	Function(pHeapPlayer);
	delete pHeapPlayer;
	ShowStatus();

	const int numberOfPlayers{ 5 };
	Player* m_Players[numberOfPlayers]{};
	for (int i{}; i < numberOfPlayers; ++i)
	{
		std::cout << m_Players[i] << ' ';
	}
	std::cout << '\n';

	for (int k{}; k < numberOfPlayers; ++k)
	{
		m_Players[k] = new Player{ std::string("Player number") + std::to_string(k) };
	}
	std::cout << '\n';

	for (int i{}; i < numberOfPlayers; ++i)
	{
		m_Players[i]->ShowMessage();

	}
	std::cout << '\n';

	for (int j{}; j < numberOfPlayers; ++j)
	{
		std::cout << m_Players[j] << ' ';
	}

	std::cout << '\n';
	ShowStatus();
	std::cout << '\n';

	for (int l{}; l < numberOfPlayers; ++l)
	{
	 	delete m_Players[l];
		m_Players[l] = nullptr;
	}
	ShowStatus();
	std::cout << '\n';

	pHeapPlayer = nullptr;

}

void Function(Player* pPlayer)
{
	pPlayer->SetScore(42);
	pPlayer->ShowMessage();
}

void ShowStatus()
{
	std::cout << "Number of Players is: " << Player::GetNumberOfPlayers() << '\n';
}