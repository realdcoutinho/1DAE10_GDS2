//#include "pch.h"		
#include "Cat.h"
#include <iostream>

Cat::Cat() :m_NightVision{ false }
{
	std::cout << "Cat constructor.\n";
}

Cat::~Cat()
{
	std::cout << "Cat destructor.\n";
}

void Cat::MakeSound() const 
{
	std::cout << "Miaaaaauw\n";
}

void Cat::SetNightVision(bool b)
{
	std::cout << "Setting night vision.\n";
	m_NightVision = b;
}

