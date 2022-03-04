#include "pch.h"

#include "Cat.h"
#include "Dog.h"
#include <vector>

int main()
{
	std::cout << "\n\n\nVector of base class pointers\n";
	std::vector<Animal*>animals;
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
	for (Animal*pAnimal : animals)
	{
		delete pAnimal;
	}


	std::cin.get();
	return 0;
}

