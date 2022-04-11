#include "pch.h"
#include "Camera.h"
#include <iostream>
using namespace utils;

Camera::Camera(float width, float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_LevelBoundaries{}
	, m_FloorHeight{47}
	, m_GroundFloorHeight{24}
	, m_Floor{floor(0)}
	, m_CameraVelocity{ 0.f, 10.f }
	, m_CameraInterval{47}
	, m_CameraIntervalBonus{165}
{

}

void Camera::SetLevelBounderies(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::Transform(const Rectf& target, bool isGround)
{
	Point2f bottomLeft{ Track(target) };
	Clamp(bottomLeft);
	//MoveCamera(bottomLeft, target);
	SetColor(Color4f{ 0, 0, 1, 1 });
	//if (target.bottom > m_GroundFloorHeight + m_FloorHeight * int(floor::three))
	//{
	//	glTranslatef(-bottomLeftPos.x, -(m_CameraInterval), 0);
	//}
	//if (target.bottom > m_GroundFloorHeight + m_FloorHeight * int(floor::four))
	//{
	//	glTranslatef(-bottomLeftPos.x, -(m_CameraInterval), 0);
	//}
	//if (target.bottom > m_GroundFloorHeight + m_FloorHeight * int(floor::five))
	//{
	//	glTranslatef(-bottomLeftPos.x, -(m_CameraInterval), 0);
	//}
	//if (target.bottom > m_GroundFloorHeight + m_FloorHeight * int(floor::six))
	//{
	//	glTranslatef(-bottomLeftPos.x, -(m_CameraInterval), 0);
	//}
	//if (target.bottom > m_GroundFloorHeight + m_FloorHeight * int(floor::seven))
	//{
	//	glTranslatef(-bottomLeftPos.x, -(m_CameraInterval), 0);
	//}
	//if (target.bottom > m_GroundFloorHeight + m_FloorHeight * int(floor::bonus) - 20)
	//{
	//	glTranslatef(-bottomLeftPos.x, -(m_CameraIntervalBonus), 0);
	//}


	glTranslatef(-bottomLeft.x, -bottomLeft.y, 0);
	utils::DrawRect(m_BottomLeft, m_Width, m_Height);
}



void Camera::MoveCamera(Point2f& bottomLeftPos, const Rectf& target)
{
	float climberY{ target.bottom };
	if (climberY >= 160.f)
	{
		if (bottomLeftPos.y > 40)
		{
			bottomLeftPos.y = float(24 * sin(0.5 * (M_PI) * (m_ElapsedSec - 1)) + 24);
		}
		if (climberY == 160.f)
		{
			m_ElapsedSec = 0;
		}
	}
}

void Camera::Update(float elapsedSec)
{
	m_ElapsedSec += elapsedSec;
	std::cout << m_ElapsedSec << '\n';
}




Point2f Camera::Track(const Rectf& target)
{
	Point2f bottomLeftPos{ target.left + target.width / 2, target.bottom + target.height / 2 };
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
}