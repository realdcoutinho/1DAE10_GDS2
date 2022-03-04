//#include "pch.h"			
#include "Animal.h"
#include <iostream>

Animal::Animal(AnimalType animalType)
	: m_AnimalType{animalType}
{
	std::cout << "Animal constructor\n";

}

Animal::~Animal()
{
	std::cout << "Animal destructor\n";
}

//void Animal::MakeSound() const
//{
//	std::cout <<"I am an Animal, I have no idea what sound to make!\n";
//}

