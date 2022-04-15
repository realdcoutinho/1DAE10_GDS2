#pragma once
#include "NPC.h"
#include "Texture.h"
#include "utils.h"
#include "Stalagmite.h"
#include <map>
class Enemies final : public NPC
{
public:
	explicit Enemies(Point2f bottomLeft, float windowWidth, float widthText, float heightText );
	Enemies(const Enemies& other) = delete; //copy constructor
	Enemies& operator=(const Enemies& other) = delete; // assignment operator
	Enemies(Enemies&& other) = delete; // move constructor
	Enemies& operator=(Enemies&& other) = delete; // move assignment operator
	virtual ~Enemies() override; // should it be included I dont remember

	void Draw(Texture* textureOne, Texture* textureTwo) const;
	virtual void Update(float elapsedSec) override;
	void SetEnemyState(int& state, const Rectf& actorShape);


private:
	void SetMeasures();
	void SetEnemyType();

	void InitializeStalagmites();
	void DrawStalagmites() const;
	void SetVelocity();
	void UpdateStalagmites(float elapsedSec);

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

	float m_TextureWidthTemp;
	float m_TextureHeightTemp;

	Stalagmite* m_pStalagmite;
	std::map<std::string, Texture*> map;
};



