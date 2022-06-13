#include "pch.h"
#include "SVGParser.h"
#include <iostream>
#include "Level.h"
#include "Player.h"
#include "Game.h"

using namespace utils;

Level::Level(Game* game, Player* player, float windowWidth, float windowHeight)
	: m_WindowWidth	{ windowWidth }
	, m_WindowHeight{ windowHeight }
	, m_ActorShape	{}
	, m_OffSet		{100.0f}
	, m_pPlayer		{ player }
	, m_pGame		{ game }
	, m_pBackground	{ game->GetTextureManager()->GetTexturePointer("Background")}
	, m_Foreground	{ game->GetTextureManager()->GetTexturePointer("Foreground") }
	, m_pTextures	{ game->GetTextureManager() }
{
	
	SetMeasures();
	GetBackgroundRect();
	SetScale();
	SetSvgVertices(m_LevelCollitionPath, m_LevelCollison);

	InitializeBonus();
	InitializeClouds();
	InitializeBlocks();
	m_NrOfObjects = int(m_pGameObjects.size());
	
	InitializeWinningBird();
	InitializeEnemies();
	m_NrOfNPC = int(m_pNPC.size());
}

Level::~Level()
{
	DeleteTextures();
}

TextureManager* Level::GetTextureManager() const
{
	return m_pTextures;
}


void Level::SetMeasures()
{
	m_TextureWidth = m_pBackground->GetWidth();
	m_TextureHeight = m_pBackground->GetHeight();
	m_TextureRect.bottom = 0;
	m_TextureRect.left = 0;
	m_TextureRect.height = m_TextureHeight;
	m_TextureRect.width = m_TextureWidth;
}


void Level::InitializeBlocks()
{
	Point2f floorTwo{ m_OffSet + 32 , 64 };
	Point2f floorThree{ m_OffSet + 40, 112 };
	Point2f floorFour{ m_OffSet + 40, 160 };
	Point2f floorFive{ m_OffSet + 40, 208 };
	Point2f floorSix{ m_OffSet + 48, 256 };
	Point2f floorSeven{ m_OffSet + 48, 304 };
	Point2f floorEight{ m_OffSet + 48, 352 };
	int nrOfGreenBlocksRow{ 24 };
	int nrOfBrownBlocksRow{ 22 };
	int nrOfBlueBlocksRow{ 20 };

	int NrOfBlocks = nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 + nrOfBlueBlocksRow * 3; //146 blocks

	for (int i{}; i < NrOfBlocks; ++i)
	{
		float width{8};
		if (i < nrOfGreenBlocksRow)
		{
			m_pGameObjects.push_back(new Blocks{this, floorTwo, (int)BlockType::green});
			floorTwo.x += width;
		}
		if (i >= nrOfGreenBlocksRow && i < nrOfGreenBlocksRow + nrOfBrownBlocksRow)
		{
			m_pGameObjects.push_back(new Blocks{ this, floorThree, (int)BlockType::brown});
			floorThree.x += width;
		}
		if (i >= nrOfGreenBlocksRow + nrOfBrownBlocksRow && i < nrOfGreenBlocksRow + nrOfBrownBlocksRow * 2)
		{
			m_pGameObjects.push_back(new Blocks{ this,  floorFour, static_cast<int>(BlockType::brown)});
			floorFour.x += width;
		}
		if (i >= nrOfGreenBlocksRow + nrOfBrownBlocksRow * 2 && i < nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3)
		{
			m_pGameObjects.push_back(new Blocks{ this, floorFive, (int)BlockType::brown});
			floorFive.x += width;
		}
		if (i >= nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 && i < nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 + nrOfBlueBlocksRow)
		{
			m_pGameObjects.push_back(new Blocks{ this, floorSix, (int)BlockType::blue});
			floorSix.x += width;
		}
		if (i >= nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 + nrOfBlueBlocksRow && i < nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 + nrOfBlueBlocksRow * 2)
		{
			m_pGameObjects.push_back(new Blocks{ this, floorSeven, (int)BlockType::blue});
			floorSeven.x += width;
		}
		if (i >= nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 + nrOfBlueBlocksRow * 2 && i < nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 + nrOfBlueBlocksRow * 3)
		{
			m_pGameObjects.push_back(new Blocks{ this,  floorEight, (int)BlockType::blue});
			floorEight.x += width;
		}
	}
	m_NrOfObjects = int(m_pGameObjects.size());
}

void Level::InitializeClouds()
{
	Point2f cloudOne{ m_OffSet + 85, 100 };
	Point2f cloudTwo{ m_OffSet + 170, 480 };
	Point2f cloudThree{ m_OffSet + 122, 610 };

	//m_pGameObjects.push_back(new Cloud(this, cloudOne, 10, int(CloudType::top), m_TextureWidth));
	m_pGameObjects.push_back(new Cloud(this, cloudTwo, 7, int(CloudType::bottom), m_TextureWidth));
	m_pGameObjects.push_back(new Cloud(this, cloudThree, 6, int(CloudType::bottom), m_TextureWidth));

	m_NrOfObjects = int(m_pGameObjects.size());
}

void Level::InitializeBonus()
{
	Point2f bonusOne{ m_OffSet + 31.f, 409.f };
	Point2f bonusTwo{ m_OffSet + 216.f, 409.f };
	Point2f bonusThree{ m_OffSet + 50.f, 537.f };
	Point2f bonusFour{ m_OffSet + 71.f, 665.f };

	m_pGameObjects.push_back(new Bonus(this, bonusOne));
	m_pGameObjects.push_back(new Bonus(this, bonusTwo));
	m_pGameObjects.push_back(new Bonus(this, bonusThree));
	m_pGameObjects.push_back(new Bonus(this, bonusFour));

	m_NrOfObjects = int(m_pGameObjects.size());
}

void Level::UpdateGameObjects(float elapsedSec)
{
	for (int i{}; i < m_NrOfObjects; ++i)
	{
		m_pGameObjects[i]->Update(elapsedSec);
	}
}



void Level::InitializeWinningBird()
{
	Point2f winningBird{ 66.f, 835.f };
	m_pNPC.push_back(new WinningBird(m_pPlayer, this, winningBird, m_TextureWidth));
	m_NrOfNPC = int(m_pNPC.size());
}

void Level::InitializeEnemies()
{
	Point2f enemyOne{ m_OffSet + 150.f, 72.f };
	Point2f enemyTwo{ m_OffSet + 95.f, 120.f };
	Point2f enemyThree{ m_OffSet + 200.f, 168.f };
	Point2f enemyFour{ m_OffSet + 216.f, 216.f };
	Point2f enemyFive{ m_OffSet + 148.f, 264.f };
	Point2f enemySix{ m_OffSet + 232.f,312.f };
	Point2f enemySeven{ m_OffSet + 252.f, 360.f };

	m_pNPC.push_back(new WalkingEnemy(m_pPlayer, this,  enemyOne, m_TextureWidth));
	m_pNPC.push_back(new WalkingEnemy(m_pPlayer, this, enemyTwo, m_TextureWidth));
	m_pNPC.push_back(new WalkingEnemy(m_pPlayer, this, enemyThree, m_TextureWidth));
	m_pNPC.push_back(new WalkingEnemy(m_pPlayer, this, enemyFour, m_TextureWidth));
	m_pNPC.push_back(new WalkingEnemy(m_pPlayer, this, enemyFive, m_TextureWidth));
	m_pNPC.push_back(new WalkingEnemy(m_pPlayer, this, enemySix, m_TextureWidth));
	m_pNPC.push_back(new WalkingEnemy(m_pPlayer,this, enemySeven, m_TextureWidth));
	m_NrOfNPC = int(m_pNPC.size());
}

void Level::Draw() const
{
	DrawBackground();
	DrawNPC();
	//DrawForeground();
	DrawGameObjects();
	
	for (int i{}; i < m_LevelCollison.size(); ++i)
	{
		DrawPolygon(m_LevelCollison[i]);
	}

}

void Level::DrawBackground() const
{
	m_pBackground->Draw(Point2f{ m_OffSet + 0, 0});
}

void Level::DrawForeground() const
{
	m_pTextures->GetTexturePointer(std::string{ "Foreground" })->Draw(Point2f{ m_OffSet + 0,0 });
	//m_pForeGround->Draw(Point2f{ 0,0 });
}

void Level::DrawGameObjects() const
{
	for (int i{}; i < m_NrOfObjects; ++i)
	{
		m_pGameObjects[i]->Draw();
		if (typeid(*m_pGameObjects[i]) == typeid(Blocks))
		{
			Blocks* pBlocks{ dynamic_cast<Blocks*>(m_pGameObjects[i]) };
			if (pBlocks)
				pBlocks->Draw();
		}
		if (typeid(*m_pGameObjects[i]) == typeid(Bonus))
		{
			m_pGameObjects[i]->Draw();

			//Bonus* pBonus{ dynamic_cast<Bonus*>(m_pGameObjects[i]) };
			//if (pBonus)
			//	pBonus->Draw(m_pTextures->GetTexturePointer(std::string{ "Bonus" }));
		}
	}
}

void Level::DrawNPC() const
{
	for (int i{}; i < m_NrOfNPC; ++i)
	{
		if (typeid(*m_pNPC[i]) == typeid(WalkingEnemy))
		{
			WalkingEnemy* pEnemies{ dynamic_cast<WalkingEnemy*>(m_pNPC[i]) };
			if (pEnemies)
				pEnemies->Draw();
		}
		if (typeid(*m_pNPC[i]) == typeid(WinningBird))
		{
			WinningBird* pWinningBird{ dynamic_cast<WinningBird*>(m_pNPC[i]) };
			if (pWinningBird)
				pWinningBird->Draw();
		}
	}
}

void Level::Update(float elapsedSec)
{
	UpdateGameObjects(elapsedSec);
	UpdateNPC(elapsedSec);
}

void Level::SetActorShape(const Rectf& actorShape)
{
	m_ActorShape = actorShape;
	GameObjectOverlap(actorShape);
	SetCloudVelocity(actorShape);
}

void Level::UpdateNPC(float elapsedSec)
{
	for (int i{}; i < m_NrOfNPC; ++i)
	{
		m_pNPC[i]->Update(elapsedSec);
		if (typeid(*m_pNPC[i]) == typeid(WalkingEnemy))
		{
			WalkingEnemy* pEnemies{ dynamic_cast<WalkingEnemy*>(m_pNPC[i]) };
			if (pEnemies)
				pEnemies->SetEnemyState(m_PlayerState, m_ActorShape);
		}
	}
}



void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	HandleCollisionLevel(actorShape, actorVelocity);
	HandleCollisionGameObjects(actorShape, actorVelocity);
}

void Level::HandleCollisionLevel(Rectf& actorShape, Vector2f& actorVelocity) const
{
	Point2f actorBottomCenter{ actorShape.GetBottomCenter(0, -1) };
	Point2f actorTopCenter{ actorShape.GetBottomCenter(0, actorShape.height) };

	//Point2f actorCenterLeft{ actorShape.left , actorShape.bottom + actorShape.height };
	//Point2f actorCenterRight{ actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height };
	//Point2f bottomLeft{ actorShape.left, actorShape.bottom }; //bottomLeft
	//Point2f bottomRight{ actorShape.left + actorShape.width, actorShape.bottom }; //bottomRight
	//Point2f topLeft{ actorShape.left, actorShape.bottom + actorShape.height }; //topLeft
	//Point2f topRight{ actorShape.left + actorShape.width, actorShape.bottom + actorShape.height }; //TopRight

	HitInfo hitInfo{};
	size_t collison{ m_LevelCollison.size() };
	for (size_t i{ 0 }; i < collison; ++i)
	{
		if (Raycast(m_LevelCollison[i], actorBottomCenter, actorTopCenter, hitInfo) && actorVelocity.y <= 0) // down to top
		{
			actorShape.bottom = hitInfo.intersectPoint.y;
			actorVelocity.y = 0;
		}
		if (Raycast(m_LevelCollison[i], actorTopCenter, actorBottomCenter, hitInfo) && actorVelocity.y < 0) // top down
		{
			actorVelocity.y = -actorVelocity.y;
		}
		if (Raycast(m_LevelCollison[i], actorBottomCenter, actorTopCenter, hitInfo) && actorVelocity.y < 0) // top down
		{
			actorVelocity.y = -actorVelocity.y;
		}
		//////////////if (Raycast(m_LevelCollison[i], bottomLeft, topLeft, hitInfo) && actorVelocity.y <= 0) // down to top
		//////////////{
		//////////////	actorShape.bottom = hitInfo.intersectPoint.y;
		//////////////	actorVelocity.y = 0;
		//////////////}
		//////////////if (Raycast(m_LevelCollison[i], bottomRight, topRight, hitInfo) && actorVelocity.y <= 0) // down to top
		//////////////{
		//////////////	actorShape.bottom = hitInfo.intersectPoint.y;
		//////////////	actorVelocity.y = 0;
		//////////////}
		//////////////if (Raycast(m_LevelCollison[i], topLeft, bottomLeft, hitInfo) && actorVelocity.y > 0) // top down
		//////////////{
		//////////////	actorVelocity.y = -actorVelocity.y;
		//////////////}
		//////////////if (Raycast(m_LevelCollison[i], topRight, bottomRight, hitInfo) && actorVelocity.y > 0) // top down
		//////////////{
		//////////////	actorVelocity.y = -actorVelocity.y;
		//////////////}
		//if (Raycast(m_LevelCollison[i], actorCenterLeft, actorCenterRight, hitInfo)) // left to right bottom
		//{
		//	actorVelocity.y = 0;
		//	actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
		//	std::cout << "HIT ONE" << '\n';
		//}
		//if (Raycast(m_LevelCollison[i], actorCenterRight, actorCenterLeft, hitInfo)) // left to right bottom
		//{
		//	actorVelocity.y = 0;
		//	actorShape.left = hitInfo.intersectPoint.x;
		//	std::cout << "HIT" << '\n';
		//}
		//////////if (Raycast(m_LevelCollison[i], bottomLeft, bottomRight, hitInfo)) // left to right bottom
		//////////{
		//////////	actorVelocity.y = 0;
		//////////	actorShape.left = hitInfo.intersectPoint.x;
		//////////	std::cout << "HIT" << '\n';
		//////////}
		//////////if (Raycast(m_LevelCollison[i], bottomRight, bottomLeft, hitInfo)) // left to right bottom
		//////////{
		//////////	actorVelocity.y = 0;
		//////////	actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
		//////////	std::cout << "HIT" << '\n';
		//////////}
		//////////if (Raycast(m_LevelCollison[i], topLeft, topRight, hitInfo)) // left to right bottom
		//////////{
		//////////	actorVelocity.y = 0;
		//////////	actorShape.left = hitInfo.intersectPoint.x;
		//////////	std::cout << "HIT" << '\n';
		//////////}
		//////////if (Raycast(m_LevelCollison[i], topRight, topLeft, hitInfo)) // left to right bottom
		//////////{
		//////////	actorVelocity.y = 0;
		//////////	actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
		//////////	std::cout << "HIT" << '\n';
		//////////}
		//if (Raycast(m_LevelCollison[i], bottomLeft, bottomRight, hitInfo)) // left to right bottom
		//{
		//	actorVelocity.y = 0;
		//	actorShape.left = hitInfo.intersectPoint.x + 1;
		//	std::cout << "HIT" << '\n';
		//}
		//if (Raycast(m_LevelCollison[i], bottomRight, bottomLeft, hitInfo)) // left to right bottom
		//{
		//	actorVelocity.y = 0;
		//	actorShape.left = hitInfo.intersectPoint.x - actorShape.width - 1;
		//	std::cout << "HIT" << '\n';
		//}
	}
}


void Level::HandleBlocksEnemyCollison()
{
	for (int i{}; i < m_NrOfObjects; ++i)
	{
		if (typeid(*m_pGameObjects[i]) == typeid(Blocks))
		{

		}
	}
}


void Level::HandleCollisionGameObjects(Rectf& actorShape, Vector2f& actorVelocity) const
{
	for (int i{ 0 }; i < m_NrOfObjects; ++i)
	{
		if (typeid(*m_pGameObjects[i]) == typeid(Blocks))
		{
			Platform* pPlatform{ dynamic_cast<Platform*>(m_pGameObjects[i]) };
			if (pPlatform)
				pPlatform->HandleCollision(actorShape, actorVelocity);
		}
		if (typeid(*m_pGameObjects[i]) == typeid(Cloud))
		{
			Platform* pPlatform{ dynamic_cast<Platform*>(m_pGameObjects[i]) };
			if (pPlatform)
				pPlatform->HandleCollision(actorShape, actorVelocity);
		}
	}
}

bool Level::IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity) const
{
	if (IsOnGroundLevel(actorShape, actorVelocity))
		return true;
	if (IsOnGroundGameObjects(actorShape, actorVelocity))
		return true;
	else
		return false;
}

bool Level::IsOnGroundLevel(const Rectf& actorShape, Vector2f& actorVelocity) const
{
	Point2f actorBottomCenter{ actorShape.GetBottomCenter(0, -1) };
	Point2f actorTopCenter{ actorShape.GetBottomCenter(0, actorShape.height) };

	size_t collison{ m_LevelCollison.size() };
	for (size_t i{ 0 }; i < collison; ++i)
	{
		HitInfo hitInfo{};
		if (Raycast(m_LevelCollison[i], actorBottomCenter, actorTopCenter, hitInfo) && actorVelocity.y == 0)
			return true;
		if (Raycast(m_LevelCollison[i], actorTopCenter, actorBottomCenter, hitInfo) && actorVelocity.y >= 0)
			return false;
	}
	return false;
}

bool Level::IsOnGroundGameObjects(const Rectf& actorShape, Vector2f& actorVelocity) const
{
	for (int i{ 0 }; i < m_NrOfObjects; ++i)
	{
		if (typeid(*m_pGameObjects[i]) == typeid(Blocks))
		{
			Platform* pPlatfrom{static_cast<Platform*>(m_pGameObjects[i])};
			if (pPlatfrom)
				if (pPlatfrom->IsOnGround(actorShape, actorVelocity))
					return true;
		}
		if (typeid(*m_pGameObjects[i]) == typeid(Cloud))
		{
			Platform* pPlatfrom{ static_cast<Platform*>(m_pGameObjects[i]) };
			if (pPlatfrom)
				if (pPlatfrom->IsOnGround(actorShape, actorVelocity))
					return true;
		}
	}
	return false;
}

bool Level::IsOnCloud(const Rectf& actorShape, Vector2f& actorVelocity) const
{
	for (int i{ 0 }; i < m_NrOfObjects; ++i)
	{
		if (typeid(*m_pGameObjects[i]) == typeid(Cloud))
		{
			Cloud* pCloud{ static_cast<Cloud*>(m_pGameObjects[i]) };
			if (pCloud)
				if (pCloud->IsOnGround(actorShape, actorVelocity))
					return true;
		}
	}
	return false;
}

void Level::GameObjectOverlap(const Rectf& actorShape)
{
	for (size_t i{}; i < m_pGameObjects.size(); ++i)
	{
		if (typeid(*m_pGameObjects[i]) == typeid(Stalagtites))
		{
			Stalagtites* pStalagtite{ static_cast<Stalagtites*>(m_pGameObjects[i]) };
			if (pStalagtite)
				pStalagtite->Overlap(actorShape);
		}
		if (typeid(*m_pGameObjects[i]) == typeid(Stalagmite))
		{
			Stalagmite* pStalagtite{ static_cast<Stalagmite*>(m_pGameObjects[i]) };
			if (pStalagtite)
				pStalagtite->Overlap(actorShape);
		}
		m_pGameObjects[i]->Overlap(actorShape);
	}
}

void Level::NPCOverlap(const Rectf& actorShape)
{
	for (int i{}; i < m_NrOfNPC; ++i)
	{
		m_pNPC[i]->Overlap(actorShape);
	}
}

void Level::DeleteTextures()
{
	for (int i{}; i < m_NrOfObjects; ++i)
	{
		delete m_pGameObjects[i];
	}

	for (int i{}; i < m_NrOfNPC; ++i)
	{
		delete m_pNPC[i];
	}
}




void Level::SetCloudVelocity(const Rectf& actorShape)
{
	for (int i{ 0 }; i < m_pGameObjects.size(); ++i)
	{
		if (typeid(*m_pGameObjects[i]) == typeid(Cloud))
		{
			Cloud* pCloud{ static_cast<Cloud*>(m_pGameObjects[i]) };
			if (pCloud)
				if (pCloud->IsOnGround(actorShape))
					m_CloudVelocity = pCloud->GetVelocity();
		}
	}
}

Vector2f Level::GetCloudVelocityVector() const
{
	return m_CloudVelocity;
}

bool Level::IsWinning() const
{
	for (int i{}; i < m_NrOfNPC; ++i)
	{
		if(typeid(*m_pNPC[i]) == typeid(WinningBird))
			return m_pNPC[i]->Overlap(m_ActorShape);
	}
	return false;
}

float Level::GetScale() const
{
	return m_Scale;
}

Rectf Level::GetBoundaries() const
{
	Rectf boundries{m_TextureRect.left + m_OffSet, m_TextureRect.bottom, m_TextureRect.width, m_TextureRect.height};
	return boundries;
	//return m_TextureRect;
}

void Level::SetSvgVertices(const std::string& svgPath, std::vector<std::vector<Point2f>>& svgVertices)
{
	if (SVGParser::GetVerticesFromSvgFile(svgPath, svgVertices)) {}
	else { std::cout << "Level failed to load from svg" << std::endl; }
}

Rectf Level::GetBackgroundRect()
{
	//return Rectf{ m_TextureRect.left, m_TextureRect.bottom, m_TextureRect.width, m_TextureRect.height };
	return m_TextureRect;
}

void Level::GetPlayerState(int state)
{
	m_PlayerState = state;
}

void Level::SetScale()
{
	m_Scale = m_WindowWidth / m_TextureWidth; // by deviding the window width by the texture width I get a ration to use in my camera
}


Rectf Level::GetActorShape()
{
	return m_ActorShape;
}

Player* Level::GetPlayerPointer()
{
	return m_pPlayer;
}

int Level::GetBlockIndex(Rectf& actorShape, Vector2f& actorVelocity)
{
	int value{0};
	for (int i{}; i < m_NrOfObjects; ++i)
	{
		if (typeid(*m_pGameObjects[i]) == typeid(Blocks))
		{
			Platform* pPlatfrom{ static_cast<Platform*>(m_pGameObjects[i]) };
			if (pPlatfrom)
			{
				if (!(pPlatfrom->IsOnGround(actorShape, actorVelocity)) && pPlatfrom->m_IsDestroyed && pPlatfrom->IsOnGroundStalgmite(actorShape))
				{
					return i;
				}
			}
		}
	}
	return value;
}

void Level::SetBlockFixed(int index)
{
	if (typeid(*m_pGameObjects[index]) == typeid(Blocks))
	{
		Blocks* pBlocks{ static_cast<Blocks*>(m_pGameObjects[index]) };
		if (pBlocks)
			pBlocks->FixedBlocked();
	}
}

