// 07Classes1HandsonTheory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Player.h"

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

	Function(pHeapPlayer);
}

void Function(Player* pPlayer)
{
	pPlayer->SetScore(42);
	pPlayer->ShowMessage();
}

