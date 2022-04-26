#pragma once
#include "Damage.h"
#include "Texture.h"
#include "Animation.h"
#include "utils.h"

class Level;
class Stalagmite final : public Damage 
{
public:
	explicit Stalagmite(Level* level, Point2f bottomLeft, float m_PositionOffSet);
	Stalagmite(const Stalagmite& other) = delete; //copy constructor
	Stalagmite& operator=(const Stalagmite& other) = delete; // assignment operator
	Stalagmite(Stalagmite&& other) = delete; // move constructor
	Stalagmite& operator=(Stalagmite&& other) = delete; // move assignment operator
	~Stalagmite();

	void Draw(Point2f bottomLeft) const;
	virtual void Update(float elapsedSec) override;

private:
	void SetMeasures();
	void InitializeAnimations();
	void UpdateState(float elapsedSec);

	enum class State
	{
		form = 0,
		destroyed = 1
	};


	float m_Time;
	bool m_IsDestroyed;
	float m_PositionOffSet;
	State m_State;

	Animation* m_pAnimationStalagmiteForm;
	Animation* m_pAnimationStalagmiteDestroyed;
	Texture* m_pTextureStalagmite;
	Rectf m_SourceRect;
};

