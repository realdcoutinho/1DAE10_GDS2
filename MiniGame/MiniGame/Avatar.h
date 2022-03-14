#pragma once
#include "utils.h"

class Level;
class Avatar
{
public:
	enum class ActionState
	{
		waiting = 1,
		moving = 2,
		transforming = 3
	};

	Avatar();
	~Avatar();
	void Update(float elapsedSec, const Level* level);
	void Draw();
	void PowerUpHit();
	Rectf GetShape();

private:
	Rectf m_Shape{ 50, 280, 36, 97 };
	float m_HorSpeed{ 200.0f };
	float m_JumpSpeed{ 600.0f };
	Vector2f m_Velocity{ 0.0f, 0.0f };
	Vector2f m_Acceleration{ 0.0f, -981.0f };
	ActionState m_ActionState = ActionState::moving;
	float m_AccuTransformSec{ 0.0f };
	float m_MaxTransformSec{ 1.0f };
	int m_Power{ 0 };


	void Move(float elapsedSec);
	void Transform(float elapsedSec);

};

