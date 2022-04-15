#pragma once
#include "Damage.h"
class Stalagtites final : public Damage
{
public:
	Stalagtites(Point2f bottomLeft, float m_PositionOffSet);
	Stalagtites(const Stalagtites& other) = delete; //copy constructor
	Stalagtites& operator=(const Stalagtites& other) = delete; // assignment operator
	Stalagtites(Stalagtites&& other) = delete; // move constructor
	Stalagtites& operator=(Stalagtites&& other) = delete; // move assignment operator

	~Stalagtites();
private:
};

