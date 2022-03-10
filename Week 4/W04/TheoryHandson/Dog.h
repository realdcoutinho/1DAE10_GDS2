#pragma once
#include "Animal.h"

class Dog final : public Animal
{
public:
	Dog();
	virtual ~Dog();
	void MakeSound()const;
	void SetSurveillanceMode(bool value);
private:
	bool m_SurveillanceMode;
};

 
