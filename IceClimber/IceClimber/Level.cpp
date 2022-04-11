#include "pch.h"
#include "SVGParser.h"
#include <iostream>
#include "Level.h"
using namespace utils;

Level::Level(float windowWidth, float windowHeight)
	: m_pBackground{new Texture("./Images/Background.png")}
	, m_pForeGround{ new Texture("./Images/Foreground.png") }
	, m_WindowWidth{ windowWidth }
	, m_WindowHeight{ windowHeight }
	, m_NrOfTypesBlocks{3}
	, m_CloudIndex{0}
{
	SetMeasures();
	GetBackgroundRect();
	SetScale();
	SetSvgVertices(m_LevelCollitionPath, m_LevelCollison);
	InitializeBlocks();
	InitializeClouds();
}

Level::~Level()
{
	DeleteTextures();

}

void Level::SetMeasures()
{
	m_TextureHeight = m_pBackground->GetHeight();
	m_TextureWidth = m_pBackground->GetWidth();

	m_TextureRect.bottom = 0;
	m_TextureRect.left = 0;
	m_TextureRect.height = m_TextureHeight;
	m_TextureRect.width = m_TextureWidth;
}

Rectf Level::GetBackgroundRect()
{
	return m_TextureRect;
}

void Level::SetScale()
{
	m_Scale = m_WindowWidth / m_TextureWidth; // by deviding the window width by the texture width I get a ration to use in my camera
}

void Level::SetSvgVertices(const std::string& svgPath, std::vector<std::vector<Point2f>>& svgVertices)
{
	if (SVGParser::GetVerticesFromSvgFile(svgPath, svgVertices)) {}
	else { std::cout << "Level failed to load from svg" << std::endl; }
}

void Level::InitializeBlocks()
{
	Point2f floorTwo{ 32, 64 };
	Point2f floorThree{ 40, 112 };
	Point2f floorFour{ 40, 160 };
	Point2f floorFive{ 40, 208 };
	Point2f floorSix{ 48, 256 };
	Point2f floorSeven{ 48, 304 };
	Point2f floorEight{ 48, 352 };
	int nrOfGreenBlocksRow{ 24 };
	int nrOfBrownBlocksRow{ 22 };
	int nrOfBlueBlocksRow{ 20 };

	m_NrOfBlocks = nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 + nrOfBlueBlocksRow * 3; //146 blocks
	int currentBlockNumbers{};
	m_NrOfBlocks = nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 + nrOfBlueBlocksRow * 3;

	for (int i{}; i < m_NrOfBlocks; ++i)
	{
		if (i < nrOfGreenBlocksRow)
		{
			m_pBlocks.push_back(new Blocks{ floorTwo, m_NrOfTypesBlocks, (int)BlockType::green });
			floorTwo.x += m_pBlocks[0]->GetWidth();
			++currentBlockNumbers;
		}
		if (i >= nrOfGreenBlocksRow && i < nrOfGreenBlocksRow + nrOfBrownBlocksRow)
		{
			m_pBlocks.push_back(new Blocks{ floorThree, m_NrOfTypesBlocks, (int)BlockType::brown });
			floorThree.x += m_pBlocks[0]->GetWidth();
			++currentBlockNumbers;
		}
		if (i >= nrOfGreenBlocksRow + nrOfBrownBlocksRow && i < nrOfGreenBlocksRow + nrOfBrownBlocksRow * 2)
		{
			m_pBlocks.push_back(new Blocks{ floorFour, m_NrOfTypesBlocks, (int)BlockType::brown });
			floorFour.x += m_pBlocks[0]->GetWidth();
			++currentBlockNumbers;
		}
		if (i >= nrOfGreenBlocksRow + nrOfBrownBlocksRow * 2 && i < nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3)
		{
			m_pBlocks.push_back(new Blocks{ floorFive, m_NrOfTypesBlocks, (int)BlockType::brown });
			floorFive.x += m_pBlocks[0]->GetWidth();
			++currentBlockNumbers;
		}
		if (i >= nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 && i < nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 + nrOfBlueBlocksRow)
		{
			m_pBlocks.push_back(new Blocks{ floorSix, m_NrOfTypesBlocks, (int)BlockType::blue });
			floorSix.x += m_pBlocks[0]->GetWidth();
			++currentBlockNumbers;
		}
		if (i >= nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 + nrOfBlueBlocksRow && i < nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 + nrOfBlueBlocksRow * 2)
		{
			m_pBlocks.push_back(new Blocks{ floorSeven, m_NrOfTypesBlocks, (int)BlockType::blue });
			floorSeven.x += m_pBlocks[0]->GetWidth();
			++currentBlockNumbers;
		}
		if (i >= nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 + nrOfBlueBlocksRow * 2 && i < nrOfGreenBlocksRow + nrOfBrownBlocksRow * 3 + nrOfBlueBlocksRow * 3)
		{
			m_pBlocks.push_back(new Blocks{ floorEight, m_NrOfTypesBlocks, (int)BlockType::blue });
			floorEight.x += m_pBlocks[0]->GetWidth();
			++currentBlockNumbers;
		}
	}
	int numbers = currentBlockNumbers;
	m_NrOfBlocks = int(m_pBlocks.size());
}

void Level::InitializeClouds()
{
	Point2f CloudOne{ 85, 100 };
	Point2f cloudTwo{ 170, 480 };
	Point2f cloudThree{ 122, 603 };

	m_pClouds.push_back(new Cloud(CloudOne, 3, int(CloudType::top), m_TextureWidth));
	m_pClouds.push_back(new Cloud(cloudTwo, 5, int(CloudType::bottom), m_TextureWidth));
	m_pClouds.push_back(new Cloud(cloudThree, 4, int(CloudType::bottom), m_TextureWidth));

	m_NrOfClouds = int(m_pClouds.size());
	for (int i{ 0 }; i < m_NrOfClouds; ++i)
	{
		m_CloudVelocity.push_back(Vector2f{ m_pClouds[i]->GetVelocity() });
	}
}

void Level::Draw() const
{
	DrawBackground();
	//SetColor(Color4f{ 1, 0, 0, 1 });
	//for (int i{}; i < m_LevelCollison.size(); ++i)
	//{
	//	DrawPolygon(m_LevelCollison[i], true, 3);
	//}

	//enemies should be drawn here
	DrawForeground();
	DrawBlocks();
	DrawClouds();
}

void Level::DrawBackground() const
{
	m_pBackground->Draw(Point2f{0,0});
}

void Level::DrawForeground() const
{
	m_pForeGround->Draw(Point2f{ 0,0 });
}

void Level::DrawBlocks() const
{
	for (int i{}; i < m_NrOfBlocks; ++i)
	{
		m_pBlocks[i]->Draw();
	}
}

void Level::DrawClouds() const
{
	for (int i{ 0 }; i < m_NrOfClouds; ++i)
	{
		m_pClouds[i]->Draw();
	}
}

void Level::Update(float elapsedSec)
{
	UpdateCloud(elapsedSec);
}

void Level::UpdateCloud(float elapsedSec)
{
	for (int i{}; i < m_NrOfClouds; ++i)
	{
		m_pClouds[i]->Update(elapsedSec);
	}
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	HandleCollisionLevel(actorShape, actorVelocity);
	HandleCollisionBlocks(actorShape, actorVelocity);
	HandleCollisionCloud(actorShape, actorVelocity);
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
		if (Raycast(m_LevelCollison[i], actorTopCenter, actorBottomCenter, hitInfo) && actorVelocity.y > 0) // top down
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

void Level::HandleCollisionBlocks(Rectf& actorShape, Vector2f& actorVelocity) const
{
	for (int i{ 0 }; i < m_NrOfBlocks; ++i)
	{
		m_pBlocks[i]->HandleCollision(actorShape, actorVelocity);
	}
}

void Level::HandleCollisionCloud(Rectf& actorShape, Vector2f& actorVelocity) const
{
	for (int i{ 0 }; i < m_NrOfClouds; ++i)
	{
		m_pClouds[i]->HandleCollision(actorShape, actorVelocity);
	}
}

bool Level::IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity) const
{
	if (IsOnGroundLevel(actorShape, actorVelocity))
		return true;
	if (IsOnGroundBlocks(actorShape, actorVelocity))
		return true;
	if (IsOnCloud(actorShape, actorVelocity))
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
		if (Raycast(m_LevelCollison[i], actorTopCenter, actorBottomCenter, hitInfo) && actorVelocity.y > 0)
			return false;
	}
	return false;
}

bool Level::IsOnGroundBlocks(const Rectf& actorShape, Vector2f& actorVelocity) const
{
	for (int i{ 0 }; i < m_NrOfBlocks; ++i)
	{
		if (m_pBlocks[i]->IsOnGround(actorShape, actorVelocity))
			return true;
	}
	return false;
}

bool Level::IsOnCloud(const Rectf& actorShape, Vector2f& actorVelocity) const
{

	for (int i{ 0 }; i < m_NrOfClouds; ++i)
	{
		if (m_pClouds[i]->IsOnGround(actorShape, actorVelocity))
			return true;
	}
	return false;
}

float Level::GetScale() const
{
	return m_Scale;
}

Rectf Level::GetBoundaries() const
{
	return m_TextureRect;
}

void Level::SetCloudIndex(const Rectf& actorShape)
{
	for (int i{ 0 }; i < m_NrOfClouds; ++i)
	{
		if (m_pClouds[i]->IsOnGround(actorShape))
			m_CloudIndex = int(i);
	}
}

int Level::GetCloudIndex() const
{
	return m_CloudIndex;
}

std::vector<Vector2f> Level::GetCloudVelocityVector() const
{
	return m_CloudVelocity;
}


void Level::DeleteTextures()
{
	delete m_pBackground;
	delete m_pForeGround;
	DeleteBlocks();
	DeleteClouds();
}
void Level::DeleteBlocks()
{
	for (int i{}; i < m_NrOfBlocks; ++i)
	{
		delete m_pBlocks[i];
	}
}

void Level::DeleteClouds()
{
	for (int i{ 0 }; i < m_NrOfClouds; ++i)
	{
		delete m_pClouds[i];
	}
}
































