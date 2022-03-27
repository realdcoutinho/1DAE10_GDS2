#pragma once
#include "utils.h"
#include "Texture.h"

class Level;
class Avatar
{
public:
	enum class ActionState
	{
		waiting = 0,
		moving = 1,
		transforming = 2
	};

	Avatar();
	~Avatar();

	void Update(float elapsedSec, const Level* level);
	void Draw();
	void PowerUpHit();
	Rectf GetShape();

private:
	//given data memebrs
	const float m_HorSpeed;
	const float m_JumpSpeed;
	const float m_MaxTransformSec;
	const float m_ClipHeight;
	const float m_ClipWidth;
	const int m_NrOfFrames;
	const int m_NrOfFramesPerSec;

	const Vector2f m_Acceleration;
	const Texture* m_pSpritesTexture;

	float m_AccuTransformSec;
	int m_Power{};
	float m_AnimTime{};
	int m_AnimFrame{};

	Rectf m_Shape;
	Vector2f m_Velocity;
	ActionState m_ActionState;


	//given functions
	void Move(float elapsedSec);
	void Transform(float elapsedSec);
	void UpdateState(float elapsedSec, const Level* pLevel);
	void DrawRectAvatar() const;
	
	//my data memebers



	Rectf m_Dest;

	//my functions
	void DrawAvatarTexture();
	void UpdateFrames(float elapsedSec);
};