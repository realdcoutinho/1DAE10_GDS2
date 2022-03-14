//#include "pch.h"
#include <iostream>
#include "Game.h"
#include "Weapon.h"
#include "Enemy.h"
#include "PickUp.h"

Game::Game()
{

}
Game::~Game()
{
	for (GameObject* ptr : m_pGameObjects)
	{
		delete ptr;
	}
	m_pGameObjects.clear();
}



void Game::AddEnemy()
{
	m_pGameObjects.push_back(new Enemy());
}

void Game::AddPickUp()
{
	m_pGameObjects.push_back(new PickUp());
}

void Game::AddWeapon()
{
	m_pGameObjects.push_back(new Weapon());
}

void Game::ReportAll() const
{
	int seqNr{ 0 };

	std::cout << "--> All Game objects\n";
	for (GameObject* ptr : m_pGameObjects)
	{
		++seqNr;
		std::cout << seqNr << ": " << ptr->ToString() << "\n";
	}

}

void Game::ReportEnemies() const
{
	DoDynamicCast();
	DoStaticCast();
}

void Game::DoDynamicCast() const
{
	std::cout << "Dynamic Cast" << '\n';
	int i{};
	for (GameObject* gameObject : m_pGameObjects)
	{
		Enemy* pEnemies{ dynamic_cast<Enemy*>(gameObject) };
		if (pEnemies)
		{
			++i;
			std::cout << i << ": Enemy " << pEnemies->ToString() << '\n';
		}
	}
}

void Game::DoStaticCast() const
{
	std::cout << "Static Cast" << '\n';
	int i{};
	for (GameObject* gameObject : m_pGameObjects)
	{
		if (typeid(*gameObject) == typeid(Enemy))
		{
			++i;
			Enemy* pEnemies{ static_cast<Enemy*>(gameObject) };
			std::cout << i << ": Enemy " << pEnemies->ToString() << '\n';
		}
	}
}