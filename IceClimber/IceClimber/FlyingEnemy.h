#pragma once
#include "NPC.h"
#include "Texture.h"
#include "Level.h"
#include "Animation.h"
#include "utils.h"

class Player;
class Level;
class FlyingEnemy final : public NPC
{
public:
	explicit FlyingEnemy(Player* player, Level* level, Point2f bottomLeft, float windowWidth);
	FlyingEnemy(const FlyingEnemy& other) = delete; //copy constructor
	FlyingEnemy& operator=(const FlyingEnemy& other) = delete; // assignment operator
	FlyingEnemy(FlyingEnemy&& other) = delete; // move constructor
	FlyingEnemy& operator=(FlyingEnemy&& other) = delete; // move assignment operator
	virtual ~FlyingEnemy() override; // should it be included I dont remember

	void Draw() const;
	virtual void Update(float elapsedSec) override;
	void SetEnemyState(int& state, const Rectf& actorShape);
private:
	void SetMeasures();
	void SetEnemyType();
	void InitializeAnimation();
	void SetVelocity();

	void UpdateAnimations(float elapsedSec);

	enum class EnemyType
	{
		bird = 2
	};

	enum class State
	{
		kill = 5,
		other = 0
	};
	State m_ActorState;
	float m_HorSpeed;

	Animation* m_pAnimationAlive;
	Animation* m_pAnimationDead;
	Texture* m_pEnemiesAlive;
	Texture* m_pEnemiesDead;


};

