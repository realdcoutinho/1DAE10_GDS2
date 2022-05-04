#include "pch.h"

#include "IntHolder.h"
#include "DataHolder.h"
#include <array>
#include <vector>
#include <string>
#include <deque>
#include <list>
#include <iostream>



template <typename T>
void PrintVector(const std::vector<T>& v);

void Templates();
void Containers();


int main()
{
	//Templates();
	Containers();

	std::cin.get();
	return 0;
}

template <typename T>
void PrintVector(const std::vector<T>& v)
{
	std::cout << "PrintVector: ";

	for (const T& value : v)
	{
		std::cout << value << ' ';
	}
	std::cout << '\n';
}

void Templates()
{
	std::vector<int>myIntVector{ 2, 3, 4 };
	PrintVector(myIntVector);

	std::vector<double>myDoubleVector{ 2.5, 3.5, 4.5 };
	PrintVector(myDoubleVector);

	std::vector<std::string>myStrings{ "Hello", "Mars", "here", "I", "come !" };
	PrintVector(myStrings);

	IntHolder *pIh{ new IntHolder{} };
	pIh->SetData(15);
	std::cout << pIh->GetData() << ' ';
	pIh->Print();

	DataHolder<int>* pDh1{ new DataHolder<int>{} };
	pDh1->SetData(15);
	std::cout << pDh1->GetData() << ' ';
	pDh1->Print();

	DataHolder<double>* pDh2{ new DataHolder<double>{} };
	pDh2->SetData(3.1415926535);
	std::cout << pDh2->GetData() << ' ';
	pDh2->Print();

	DataHolder<float>* pDh3{ new DataHolder<float>{} };
	pDh3->SetData(3.1415f);
	std::cout << pDh3->GetData() << ' ';
	pDh3->Print();

	DataHolder<std::string>* pDh4{ new DataHolder<std::string>{} };
	pDh4->SetData("Templates");
	std::cout << pDh4->GetData() << ' ';
	pDh4->Print();
}

void Containers()
{
	std::vector<int>myIntVector{};
	myIntVector.reserve(10);
	int loopCount{};
	while (loopCount++ < 20)
	{
		myIntVector.push_back(rand());
		std::cout << "Size: " << myIntVector.size() << "   Capacity: " << myIntVector.capacity() << '\n';
		//std::cin.get();
	}

	//std::deque<int> myDeque{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	//for (size_t i = 10; i < 20; i++)
	//{
	//	//myDeque.push_back(i);
	//	//.pop_front();
	//	for (int number : myDeque)
	//	{
	//		std::cout << number << ' ';
	//	}
	//	std::cout << '\n';
	//}
}