#pragma once
#include "NPC.h"
#include "Texture.h"
#include "Level.h"


class EnemyBird final : public NPC
{
public:
	explicit EnemyBird(Level* level, Point2f bottomLeft, float windowWidth, float widthText, float heightText);
	EnemyBird(const EnemyBird& other) = delete; //copy constructor
	EnemyBird& operator=(const EnemyBird& other) = delete; // assignment operator
	EnemyBird(EnemyBird&& other) = delete; // move constructor
	EnemyBird& operator=(EnemyBird&& other) = delete; // move assignment operator
	virtual ~EnemyBird() override; // should it be included I dont remember

	void Draw(Texture* textureOne, Texture* textureTwo) const;
	virtual void Update(float elapsedSec) override;
	void SetEnemyState(int& state, const Rectf& actorShape);
private:

	void SetMeasures();
	void SetVelocity();

	enum class State
	{
		kill = 5,
		other = 0
	};
	State m_ActorState;
	float m_HorSpeed;

	float m_TextureWidthTemp;
	float m_TextureHeightTemp;



};

