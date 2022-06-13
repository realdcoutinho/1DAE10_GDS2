#pragma once
#include "utils.h"
#include "Level.h"
#include "Texture.h"
#include "Animation.h"
#include <vector>
#include <unordered_map>
 
class SoundManager;
class Game;
class Player final
{
public:
	explicit Player(Game* game, Point2f center, Point2f bottomLeft);
	Player(const Player& other) = delete; //copy constructor
	Player& operator=(const Player& other) = delete; // assignment operator
	Player(Player&& other) = delete; // move constructor
	Player& operator=(Player&& other) = delete; // move assignment operator
	~Player();

	void Draw() const;
	void Update(float elapsedSec, const Level* level);
	int GetPlayerState();
	Rectf GetShape() const;
	Vector2f GetVelocity() const;
	bool GetIsOnGround() const;
	bool GetIsWinning() const;
	void SetWinning(bool isWinning);
	void SetState(int state);
	bool IsPlayerHit();

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
		dead = 1,
		roll = 0 // 0?
	};
	State m_State;

private:
	void SetMeasures();
	void SetHorizontalSpeed();
	void InitializeAnimations();

	void UpdateAnimations(float elapsedSec);
	void UpdateHorizontalVelocity(float elapsedSec, const Level* level, const Uint8* pKeysState);
	void UpdateVerticalVelocity(float elapsedsec, const Level* level, const Uint8* pKeysState);
	//void UpdateDyingMovement(float elapsedSec);
	void UpdateTimeState(float elapsedSec);

	void MoveAvatar(float elapsedSec, const Level* level);
	void Clamp(const Level* level);
	void LostLife();
	
	Game* m_pGame;
	Texture* m_pPlayerTexture;
	SoundManager* m_pSoundManager;

	float m_WidthTexture;
	float m_HeightTexture;
	float m_NrOfLifes;
	float m_NrOfColumns;
	float m_NrOfRows;
	float m_ClipWidth;
	float m_ClipHeight;
	float m_Time;
	float m_HorSpeed;
	const float m_JumpSpeed;

	bool m_FacingLeft;
	bool m_IsOnGround;
	bool m_IsWinning;
	bool m_IsDead;
	bool m_DoOnce;

	//int m_NrOfBonus; not yet implemented
	int m_NrAnimations;

	Point2f m_Center;
	Point2f m_BottomCenter;

	Rectf m_Shape;
	Rectf m_ActorShape;
	Rectf m_DestRect;
	Rectf m_SourceRect;

	Vector2f m_Velocity;
	const Vector2f m_Acceleration;
	std::vector<Animation*> m_Animations;
	
};
