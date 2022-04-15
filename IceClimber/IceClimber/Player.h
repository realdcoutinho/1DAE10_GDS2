#pragma once
#include "utils.h"
#include "Level.h"
#include "Texture.h"

class Player
{
public:
	Player(Point2f center, Point2f bottomLeft);
	~Player();

	void Draw() const;
	void Update(float elapsedSec, const Level* level);
	int GetPlayerState();
	Rectf GetShape() const;
	Vector2f GetVelocity() const;
	bool GetIsOnGround() const;
	void SetWinning(bool isWinning);

private:

	void UpdateHorizontalVelocity(float elapsedSec, const Level* level, const Uint8* pKeysState);
	void UpdateVerticalVelocity(float elapsedsec, const Level* level, const Uint8* pKeysState);

	void MoveAvatar(float elapsedSec, const Level* level);
	void Clamp(const Level* level);
	void SetMeasures();
	void SetSourceRect();
	void SetState(int state);
	Rectf GetSourceRect() const;
	void UpdateFrames(float elapsedSec);
	void SetHorizontalSpeed();

	enum class State
	{
		rest = 10,
		run = 9,
		slide = 8,
		jump = 7,
		fall = 6,
		kill = 5,
		restB = 4,
		runB = 3,
		jumpB = 2,
		dead = 2,
		roll = 0
	};

	Texture* m_pPlayerTexture;
	float m_WidthTexture;
	float m_HeightTexture;
	
	float m_AnimTime{};
	int m_AnimFrame;
	float m_NrOfFramesPerSec;
	float m_NrOfColumns;
	int m_NrOfFrames;
	float m_NrOfRows;
	float m_ClipWidth;
	float m_ClipHeight;
	//int m_NrOfBonus; not yet implemented


	bool m_FacingLeft;
	bool m_IsOnGround;
	bool m_IsWinning;


	Rectf m_DestRect;
	Rectf m_SourceRect;

	State m_State;


	const Vector2f m_Acceleration;
	float m_HorSpeed;
	const float m_JumpSpeed;
	Point2f m_Center;
	Rectf m_Shape;
	Vector2f m_Velocity;


	Point2f m_BottomCenter;

};

