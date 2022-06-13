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
	bool GetOverlap() const;
	bool GetDestroyed() const;
	void SetNewBottomLeft(Point2f bottomLeft);

private:
	void SetMeasures();
	void InitializeAnimations();
	void UpdateState(float elapsedSec);
	void FixMapBlock();


	enum class State
	{
		form = 0,
		destroyed = 1,
		used = 2
	};


	float m_OffSet;
	float m_Time;
	bool m_IsDestroyed;
	float m_PositionOffSet;
	State m_State;


	bool m_IExist{};


	Animation* m_pAnimationStalagmiteForm;
	Animation* m_pAnimationStalagmiteDestroyed;
	Texture* m_pTextureStalagmite;
	Level* m_pLevel;
	Rectf m_SourceRect;
};

