// 07Classes1HandsonTheory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Player.h"
#include <vector>

void Function(Player* pPlayer); 

int main()
{
    std::cout << "Hello World!\n";

	// object is on the heap, the pointer is on the stack!!
	Player* pHeapPlayer{ new Player{ "Mr Heap" } };
	pHeapPlayer->SetScore(20);
	
	pHeapPlayer->ShowMessage();
	Function(pHeapPlayer);

	delete pHeapPlayer;
	pHeapPlayer = nullptr;
	//Function(pHeapPlayer);

	std::vector<Player*> playerPtrs;
	for (int i{}; i < 100; ++i)
	{
		playerPtrs.push_back(new Player("Player " + std::to_string(i)));
	}
	std::cout << "Number of players: " << std::to_string(Player::GetNumberOfPlayers()) << '\n';
	for (Player* p : playerPtrs)
	{
		p->ShowMessage();
	}
	for (Player* p : playerPtrs)
	{
		delete p;
		p = nullptr;
	}
	playerPtrs.clear();
}

void Function(Player* pPlayer)
{
	pPlayer->SetScore(42);
	pPlayer->ShowMessage();
}

