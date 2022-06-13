#pragma once
#include "Damage.h"
#include "Texture.h"
#include "Animation.h"
#include "utils.h"

class Level;
class Stalagtites final : public Damage
{
public:
	Stalagtites(Level* level, Point2f bottomLeft);
	Stalagtites(const Stalagtites& other) = delete; //copy constructor
	Stalagtites& operator=(const Stalagtites& other) = delete; // assignment operator
	Stalagtites(Stalagtites&& other) = delete; // move constructor
	Stalagtites& operator=(Stalagtites&& other) = delete; // move assignment operator

	~Stalagtites();
	void Draw(Point2f bottomLeft) const;
	virtual void Update(float elapsedSec) override;
	bool GetOverlap() const;
	bool GetDestroyed() const;

private:

	void SetMeasures();
	void InitializeAnimations();
	void UpdateState(float elapsedSec);

	enum class State
	{
		forming = 0,
		falling = 1
	};
	State m_State;


	float m_CurrentTime;
	float m_FormingTime;
	bool m_IsDestroyed;

	Point2f m_OriginalBL;

	Texture* m_pTextureStalatites;
	Animation* m_pAnimationStalateiteForming;
	Animation* m_pAnimationStalagmiteFalling;
};

