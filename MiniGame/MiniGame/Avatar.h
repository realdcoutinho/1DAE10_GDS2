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
	void Draw() const;
	void PowerUpHit();
	Rectf GetShape() const;

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
	Rectf m_Dest;

	void UpdateMovement(float elapsedSec, const Level* level);
	void UpdateFrames(float elapsedSec);
	void UpdateHorizontalVelocity(float elapsedSec, const Uint8* pKeysState);
	void UpdateVerticalVelocity(float elapsedsec, const Level* level, const Uint8* pKeysState);
	void MoveAvatar(float elapsedSec, const Level* level);
	void Clamp(const Level* level);
	void HandleTransformation(float elapsedSec);
	void DrawPowerUpIndicators() const;
	Rectf GetSourceRect() const;
	Color4f GetColour() const;







	////given functions
	//void Move(float elapsedSec);
	//void Transform(float elapsedSec);
	//void UpdateState(float elapsedSec, const Level* pLevel);
	//void DrawRectAvatar() const;
	////my functions
	//void DrawAvatarTexture();
	//void UpdateFrames(float elapsedSec);
};