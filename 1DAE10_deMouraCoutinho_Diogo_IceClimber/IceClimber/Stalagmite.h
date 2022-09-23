#pragma once
#include "Damage.h"
#include "Texture.h"
#include "Animation.h"
#include "utils.h"

class Level;
class Stalagmite final : public Damage 
{
public:
	explicit Stalagmite(Level* level, Point2f bottomLeft, float offSet);
	Stalagmite(const Stalagmite& other) = delete; //copy constructor
	Stalagmite& operator=(const Stalagmite& other) = delete; // assignment operator
	Stalagmite(Stalagmite&& other) = delete; // move constructor
	Stalagmite& operator=(Stalagmite&& other) = delete; // move assignment operator
	~Stalagmite();

	void Draw(Point2f bottomLeft) const;
	virtual void Update(float elapsedSec) override;
	void SetNewBottomLeft(Point2f bottomLeft);

	bool GetOverlap() const;
	bool GetDestroyed() const;

private:
	void FixMapBlock();
	void UpdateState(float elapsedSec);
	void SetMeasures();
	void InitializeAnimations();

	enum class State
	{
		form = 0,
		destroyed = 1,
		used = 2
	};

	State m_State;

	Animation* m_pAnimationStalagmiteForm;
	Animation* m_pAnimationStalagmiteDestroyed;
	Texture* m_pTextureStalagmite;
	Level* m_pLevel;
	Rectf m_SourceRect;

	bool m_IsDestroyed;
	float m_OffSet;
	float m_Time;
	float m_PositionOffSet;
};

