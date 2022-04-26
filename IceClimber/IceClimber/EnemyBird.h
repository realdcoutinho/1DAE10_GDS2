#pragma once
#include "NPC.h"
#include "Texture.h"
#include "Level.h"
#include "Animation.h"
#include "utils.h"


class EnemyBird final : public NPC
{
public:
	explicit EnemyBird(Level* level, Point2f bottomLeft, float windowWidth);
	EnemyBird(const EnemyBird& other) = delete; //copy constructor
	EnemyBird& operator=(const EnemyBird& other) = delete; // assignment operator
	EnemyBird(EnemyBird&& other) = delete; // move constructor
	EnemyBird& operator=(EnemyBird&& other) = delete; // move assignment operator
	virtual ~EnemyBird() override; // should it be included I dont remember

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
		seal = 0,
		bear = 1,
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

