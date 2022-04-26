#include "pch.h"
#include "Camera.h"
#include <iostream>
#include "Player.h"
using namespace utils;

Camera::Camera(Player* player, float width, float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_LevelBoundaries{}
	, m_FloorHeight{47}
	, m_GroundFloorHeight{24}
	, m_Floor{floor(0)}
	, m_CameraVelocity{ 0.f, 10.f }
	, m_CameraInterval{47}
	, m_CameraIntervalBonus{165}
	, m_pPlayer{player}
{

}

Camera::~Camera()
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
	SetColor(Color4f{ 0, 0, 1, 1 });

	//if (m_pPlayer->GetShape().bottom > 164.f && m_pPlayer->GetShape().bottom < 216)
	//{
	//	bottomLeft.y = float(24 * sin(((M_PI / 2) * m_ElapsedSec) - (M_PI / 2)) + 24);
	//}

	glTranslatef(-bottomLeft.x, -bottomLeft.y, 0);
	utils::DrawRect(m_BottomLeft, m_Width, m_Height);
}



void Camera::MoveCamera(Point2f& bottomLeftPos, const Rectf& target)
{
}

void Camera::Update(float elapsedSec)
{
	//if (m_pPlayer->GetShape().bottom > 164.f && m_pPlayer->GetShape().bottom < 216)
	//{
	//	
	//	if(48 != float(24 * sin(((M_PI / 2) * m_ElapsedSec) - (M_PI / 2)) + 24))
	//	{
	//		m_ElapsedSec += elapsedSec;
	//	}
	//}
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