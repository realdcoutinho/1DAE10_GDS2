#include "pch.h"
#include "Camera.h"
#include <iostream>
using namespace utils;

Camera::Camera(float width, float height)
	: m_Width{width}
	, m_Height{height}
	, m_LevelBoundaries{0,0, width, height}
{
	std::cout << "Camera Initialized" << '\n';
	std::cout << "Camera Initialized" << '\n';
	std::cout << "Camera Initialized" << '\n';
	std::cout << "Camera Initialized" << '\n';
	std::cout << "Camera Initialized" << '\n';
}

void Camera::SetLevelBounderies(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::Transform(const Rectf& target)
{
	Point2f bottomLeftPos{ Track(target) };
	//Clamp(bottomLeftPos);
	SetColor(Color4f{ 0, 0, 1, 1 });
	glTranslatef(-bottomLeftPos.x, -bottomLeftPos.y, 0);
	utils::DrawRect(bottomLeftPos, m_Width, m_Height);
}

Point2f Camera::Track(const Rectf& target)
{
	Point2f bottomLeftPos{ target.left + target.width/2, target.bottom + target.height/2};
	bottomLeftPos.x -= m_Width / 2;
	bottomLeftPos.y -= m_Height / 2;
	return bottomLeftPos;
}

void Camera::Clamp(Point2f& bottomLeftPos)
{
	if (bottomLeftPos.x < m_LevelBoundaries.left)
	{
		bottomLeftPos.x = m_LevelBoundaries.left;
	}
	else if (bottomLeftPos.x + m_Width > m_LevelBoundaries.left + m_LevelBoundaries.width)
	{
		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width;
	}
	if (bottomLeftPos.y < m_LevelBoundaries.bottom)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom;
	}
	else if (bottomLeftPos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height;
	}

//	if (bottomLeftPos.x < m_LevelBoundaries.left)
//		bottomLeftPos.x = m_LevelBoundaries.left;
//	if (m_LevelBoundaries.left + m_LevelBoundaries.width < bottomLeftPos.x + m_Width)
//		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width;
//	if (bottomLeftPos.y < m_LevelBoundaries.bottom)
//		bottomLeftPos.y = m_LevelBoundaries.bottom;
//	if (m_LevelBoundaries.bottom + m_LevelBoundaries.height < bottomLeftPos.y + m_Height)
//		bottomLeftPos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height;
// 
	//if (bottomLeftPos.x < m_LevelBoundries.left)
	//{
	//	bottomLeftPos.x = m_LevelBoundries.left;
	//}
	//if (bottomLeftPos.x + m_Width > m_LevelBoundries.left + m_LevelBoundries.width)
	//{
	//	bottomLeftPos.x = m_LevelBoundries.left + m_LevelBoundries.width - m_Width;
	//}
	//if (bottomLeftPos.y < m_LevelBoundries.bottom)
	//{
	//	bottomLeftPos.y = m_LevelBoundries.bottom;
	//}
	//if (bottomLeftPos.y + m_Height > m_LevelBoundries.bottom + m_LevelBoundries.height)
	//{
	//	bottomLeftPos.y = m_LevelBoundries.bottom + m_LevelBoundries.height - m_Height;
	//}
//
}

