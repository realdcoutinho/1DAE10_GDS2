#pragma once
#include "utils.h"
#include "Level.h"

class Player;
class Camera final
{
public:
	explicit Camera(Player* player, float width, float height);
	Camera(const Camera& other) = delete; //copy constructor
	Camera& operator=(const Camera& other) = delete; // assignment operator
	Camera(Camera&& other) = delete; // move constructor
	Camera& operator=(Camera&& other) = delete; // move assignment operator
	~Camera();

	void SetLevelBounderies(const Rectf& levelBoundries);
	void Transform(const Rectf& target, bool isGround);

private:
	Point2f Track(const Rectf& target);
	void Clamp(Point2f& bottomLeftPos);

	Player* m_pPlayer;
	float m_Width;
	float m_Height;
	Point2f m_BottomLeft;
	Rectf m_LevelBoundaries;
};

