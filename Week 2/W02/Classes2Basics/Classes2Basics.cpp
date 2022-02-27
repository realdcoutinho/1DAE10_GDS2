// Classes2Basics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Time.h"
#include "Square.h"
#include "Container.h"
#include <vector>

void TestSquares();
void CompareTimes(const Time* t1, const Time* t2);
void PrintIntancesCntr(const std::string& message);
void TestContainer();
void PrintContainer(const Container* c);


int main()
{
    std::cout << "Hello World!\n";
    TestSquares();

    std::vector<Time*> m_Time;

    m_Time.push_back(new Time(7000));
    m_Time.push_back(new Time(2409, 123, 10));

    std::cout << '\n';
    std::cout << '\n';
    CompareTimes(m_Time[0], m_Time[1]);

    std::string numberInstaces = m_Time.at(0)->GetNrIntances();
    PrintIntancesCntr(numberInstaces);

	TestContainer();

}

void TestContainer()
{
	std::cout << "\n-- Container tests --\n";
	// Define a Container object
	const int cap{ 5 };
	std::cout << "Create container with capacity of " << cap << " elements\n";
	Container* pContainer{ new Container{cap} };
	PrintContainer(pContainer);

	// Add some values to the container
	int actNr{ 0 };
	std::cout << "\nPush back of " << (cap - 1) << " elements\n";
	for (int idx{ 1 }; idx < cap; ++idx)
	{
		pContainer->PushBack(rand() % 21);
		++actNr;
	}
	PrintContainer(pContainer);

	std::cout << "\nChange the value of the elements (using Set)\n";
	for (int idx{ 0 }; idx < actNr; ++idx)
	{
		pContainer->Set(idx, rand() % 21);
	}
	PrintContainer(pContainer);

	std::cout << "\nPush back another " << (cap - 1) << " elements\n";
	for (int i{ 1 }; i < cap; ++i)
	{
		pContainer->PushBack(rand() % 21);
		++actNr;
	}
	PrintContainer(pContainer);
	delete pContainer;
}

void PrintContainer(const Container* pContainer)
{
	std::cout << "-- Print container --\n";
	std::cout << "   Capacity: " << pContainer->Capacity() << std::endl;
	std::cout << "   Size: " << pContainer->Size() << std::endl;
	std::cout << "   Get the elements (using Get and Size)\n   ";
	for (int idx{ 0 }; idx < pContainer->Size(); ++idx)
	{
		std::cout << pContainer->Get(idx) << " ";
	}
	std::cout << std::endl;
}

void TestSquares()
{
    std::vector<Square*> m_Squares;

    for (float i{}; i < 3; ++i)
    {
        m_Squares.push_back(new Square(20 * float(i)));
    }

    for (float i{}; i < 2; ++i)
    {
        m_Squares.push_back(new Square(20 *i, 10 *i, 15 * i ));
    }

    for (Square* pSquares : m_Squares)
    {
        pSquares->Print();
    }
}

void CompareTimes(const Time* t1, const Time* t2) 
{
    std::cout << "Comparing 2 time objects" << '\n';
    t1->Print();
    t2->Print();
}

void PrintIntancesCntr(const std::string& message)
{
    std::cout << '\n';
    std::cout << "Number of instances: " << message << '\n';
    std::cout << '\n';
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
