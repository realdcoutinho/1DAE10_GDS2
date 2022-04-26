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
	void Update(float elapsedSec);




	enum class floor
	{
		zero = 0,
		one = 1, 
		two = 2,
		three = 3, 
		four = 4,
		five = 5, 
		six = 6,
		seven = 7,
		eight = 8,
		bonus = 9
	};


private:
	void MoveCamera(Point2f& bottomLeftPos, const Rectf& target);
	Vector2f m_CameraVelocity;
	float m_CameraInterval;
	float m_CameraMovement;
	float m_CameraIntervalBonus;


	Point2f m_BottomLeft;
	float m_ElapsedSec{};


	//data memebers
	float m_Width;
	float m_Height;
	Rectf m_LevelBoundaries;

	float m_FloorHeight;
	float m_GroundFloorHeight;
	floor m_Floor;


	Point2f Track(const Rectf& target);
	void Clamp(Point2f& bottomLeftPos);

	Player* m_pPlayer;
};

