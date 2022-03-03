#pragma once
class Enemy;
class Bullet;
#include "utils.h"

class Avatar
{
public:
	Avatar();
	Avatar(const Point2f& center, float width, float height);
	void Update(float elapsedSec, Enemy** pEnemies, int numEnemies);
	void Draw();
	//void SetCenter(const Point2f& center);
	//void SetDimensions(float width, float height);
	//void SetBoundries(const Rectf& boundaries);

	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);


private:
	//members
	//void Clamp();
	void HandleMoveKeyState(float elapsedSe);


	//
	Point2f m_Center;
	float m_Width;
	float m_Height;
	float m_Speed;
	Rectf m_Boundaries;

	Bullet* m_pBullet;

	//mine
	Rectf m_Avatar;
};

