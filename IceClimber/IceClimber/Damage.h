#pragma once
#include "GameObject.h"
class Damage : public GameObject
{
public:
	Damage(Point2f bottomLeft, int nrRows, int nrColumns, int nrFrames, int animFrame, float animTime, float nrFramesPerSec, float windowWidth = 0);
	Damage(const Damage& other) = delete; //copy constructor
	Damage& operator=(const Damage& other) = delete; // assignment operator
	Damage(Damage&& other) = delete; // move constructor
	Damage& operator=(Damage&& other) = delete; // move assignment operator
	
	virtual void Draw() const;
	void Update(float elapsedSec);
	void SetVelocity(Vector2f enemyVelocity = Vector2f(0, 0));
	void SetActorState(int state);
	void SetWindowWidth(float windowWith);

protected:
	void UpdateFrames(float elapsedSec);
	void UpdatePosition(float elapsedSec);
	 
	enum class ActorState
	{
		kill = 5,
		other = 0
	};
	ActorState m_ActorState;

	float m_WindowWidth;

	int m_NrOfFrames;
	int m_AnimFrame;
	float m_AnimTime;
	float m_NrOfFramesPerSec;
	Vector2f m_Velocity;
};

