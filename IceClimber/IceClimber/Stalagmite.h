#pragma once
#include "Damage.h"
#include "Texture.h"
class Stalagmite final : public Damage 
{
public:
	explicit Stalagmite(Point2f bottomLeft, float m_PositionOffSet);
	Stalagmite(const Stalagmite& other) = delete; //copy constructor
	Stalagmite& operator=(const Stalagmite& other) = delete; // assignment operator
	Stalagmite(Stalagmite&& other) = delete; // move constructor
	Stalagmite& operator=(Stalagmite&& other) = delete; // move assignment operator
	~Stalagmite();

	void Draw(Point2f bottomLeft) const;


private:
	void SetMeasures();
	void SetSourceRect();

	enum class State
	{
		form = 0,
		destroyed = 1
	};

	float m_PositionOffSet;

	State m_State;

	Texture* m_pTextureStalagmite;
	Rectf m_SourceRect;
};

