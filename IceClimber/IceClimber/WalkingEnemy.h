#pragma once
#include "NPC.h"
#include "Texture.h"
#include "utils.h"
#include "Stalagmite.h"
#include "Animation.h"

class Player;
class Level;
class WalkingEnemy final : public NPC
{
public:
	explicit WalkingEnemy(Player* player, Level* level, Point2f bottomLeft, float windowWidth);
	WalkingEnemy(const WalkingEnemy& other) = delete; //copy constructor
	WalkingEnemy& operator=(const WalkingEnemy& other) = delete; // assignment operator
	WalkingEnemy(WalkingEnemy&& other) = delete; // move constructor
	WalkingEnemy& operator=(WalkingEnemy&& other) = delete; // move assignment operator
	virtual ~WalkingEnemy() override; // should it be included I dont remember

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;
	void SetEnemyState(int& state, const Rectf& actorShape);


private:
	void UpdateVerticalVelocity(float elapsedSec);
	void UpdateHorizontalVelocity(float elapsedSec);
	void UpdatePosition(float elapsedSec);


	void SetMeasures();
	void SetEnemyType();
	void SetVelocity();
	void InitializeAnimations();

	void InitializeStalagmites();
	void DrawStalagmites() const;

	void UpdateAnimations(float elapsedSec);
	void UpdateCollisionTools();
	void UpdateStalagmites(float elapsedSec);

	void FlipXVelocity();

	static int m_NrOfEnemy;
	//void SetPlayerState();

	enum class EnemyType
	{
		seal = 0,
		bear = 1,
	};

	enum class State
	{
		kill = 5,
		other = 0
	};

	bool m_NeedsStalagmite;
	bool m_HasStalagmite;
	bool m_StalagmiteCreated;
	bool m_StalgamiteDestroyed;
	int m_BlockIndexPassDown;
	bool m_VelocityXFlipped;

	bool m_IsOffScreen;

	bool m_IsOnGround;
	const float m_InitialHeight;
	const float m_HorSpeed;


	const Vector2f m_Acceleration;
	State m_ActorState;

	float m_TimeToDestroy;


	Texture* m_pEnemiesAlive;
	Texture* m_pEnemiesDead;
	Animation* m_pAnimationAlive;
	Animation* m_pAnimationDead;
	Stalagmite* m_pStalagmite;
};



