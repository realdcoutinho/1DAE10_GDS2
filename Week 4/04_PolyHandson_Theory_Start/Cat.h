#pragma once
#include "Animal.h"

class Cat : public Animal
{
public:
	Cat( );
    ~Cat( );
    void MakeSound() const;
	void SetNightVision(bool b);
private:
	bool m_NightVision;
};

 
