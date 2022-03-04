//#include "pch.h"

#include "Cat.h"
#include "Dog.h"
#include <vector>
#include <iostream>


int main()
{
	std::cout << "\n\n\nVector of base class pointers\n";
	std::vector<Animal*>animals;
	//animals.push_back(new Animal{});
	animals.push_back(new Dog{});
	animals.push_back(new Cat{});
	animals.push_back(new Cat{});
	animals.push_back(new Dog{});
	animals.push_back(new Dog{});
	animals.push_back(new Cat{});
	for (Animal*pAnimal : animals)
	{
		pAnimal->MakeSound();
	}

	for (Animal* pAnimal : animals)
	{
		//((Dog*)pAnimal)->SetSurveillanceMode(true); // old C style typecast

		//dynamic_cast<Dog*>(pAnimal)->SetSurveillanceMode(true);
		Dog* pDog{ dynamic_cast<Dog*>(pAnimal) };
		if(pDog)pDog->SetSurveillanceMode(true);
	}

	for (Animal* pAnimal : animals)
	{
		if (typeid(*pAnimal) == typeid(Cat))
		{
			Cat* pCat{ static_cast<Cat*>(pAnimal) };

		}
	}


	for (Animal*pAnimal : animals)
	{
		delete pAnimal;
	}


	std::cin.get();
	return 0;
}

