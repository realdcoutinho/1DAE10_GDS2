#include "pch.h"			
#include "Animal.h"

Animal::Animal(){}

Animal::~Animal()
{
	std::cout << "Animal destructor\n";
}

void Animal::MakeSound() const
{
	std::cout <<"I am an Animal, I have no idea what sound to make!\n";
}

