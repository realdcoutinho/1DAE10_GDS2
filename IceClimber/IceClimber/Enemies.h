#pragma once
#include "NPC.h"
#include "Texture.h"
#include "utils.h"
#include "Stalagmite.h"
#include "Animation.h"

class Player;
class Level;
class Enemies final : public NPC
{
public:
	explicit Enemies(Player* player,Level* level, Point2f bottomLeft, float windowWidth);
	Enemies(const Enemies& other) = delete; //copy constructor
	Enemies& operator=(const Enemies& other) = delete; // assignment operator
	Enemies(Enemies&& other) = delete; // move constructor
	Enemies& operator=(Enemies&& other) = delete; // move assignment operator
	virtual ~Enemies() override; // should it be included I dont remember

	void Draw() const;
	virtual void Update(float elapsedSec) override;
	void SetEnemyState(int& state, const Rectf& actorShape);


private:
	void SetMeasures();
	void SetEnemyType();
	void SetVelocity();
	void InitializeAnimations();

	void InitializeStalagmites();
	void DrawStalagmites() const;

	void UpdateAnimations(float elapsedSec);
	void UpdateStalagmites(float elapsedSec);

	//void SetPlayerState();

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

	Player* m_pPlayer;
	Level* m_pGameLevel;
	Texture* m_pEnemiesAlive;
	Texture* m_pEnemiesDead;
	Animation* m_pAnimationAlive;
	Animation* m_pAnimationDead;
	Stalagmite* m_pStalagmite;
};



