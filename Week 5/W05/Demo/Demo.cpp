// Demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Player.h"
#include <iostream>

int main()
{
	std::cout << "Hello Worls!" << '\n';
	Player* pPlayer{ new Player{"Joe", 13} };
	std::cout << "This is a player: " << *pPlayer << '\n';
	delete pPlayer;
}
