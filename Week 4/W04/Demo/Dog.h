#pragma once
#include "Animal.h"

class Dog final : public Animal
{
public:
	Dog();
	virtual~Dog();
	virtual void MakeSound()const override;
	void SetSurveillanceMode(bool value);
private:
	bool m_SurveillanceMode;
};

 
