#include "pch.h"
#include "BaseEnemy.h"
#include "Level.h"
#include "Player.h"
#include <iostream>
using namespace utils;

//BaseEnemy::BaseEnemy(Player* player, Level* level, int enemyType, Point2f bottomLeft, float windowWidth)
//	: NPC(bottomLeft, windowWidth, 3, 4, 4, 0, 0, 10)
//	, m_pEnemiesAlive{ level->GetTextureManager()->GetTexturePointer("EnemyAlive") }
//	, m_pEnemiesDead{ level->GetTextureManager()->GetTexturePointer("EnemyDead") }
//	, m_Type { static_cast<EnemyType>(enemyType) }
//	, m_pPlayer{ player }
//	, m_HorSpeed{ 25 }
//	, m_pGameLevel{ level }
//{
//
//}



//void BaseEnemy::BaseEnemy()
//{
//	m_pAnimationAlive = new Animation(m_pEnemiesAlive, static_cast<int>(m_Type), 0, 4, 10, 4, 3);
//	m_pAnimationDead = new Animation(m_pEnemiesDead, static_cast<int>(m_Type), 0, 4, 10, 4, 3);
//}


	