#include <Windows.h>
#include <iostream>
#include <vector>
#include "Blob.h"

void DoubleNumber(int& a)
{
	std::cout << "The double of " << a << " is ";
	a *= 2;
	std::cout << a << std::endl;
}

void DoubleNumber(int&& a) //takes an r value
{
	std::cout << "The double of " << a << " is ";
	a *= 2;
	std::cout << a << std::endl;
}

void PrintDouble(const int& a)
{
	std::cout << "The double of " << a << " is ";
	std::cout << a * 2 << std::endl;
}

void DoubleNumber(Blob& blob)
{
	blob.Print();
	blob.Double();
	std::cout << "After doubling all the values in the Blob: " << '\n';
	blob.Print();
}

Blob MakeBlob(int size)
{
	Blob b{ size };
	for (int i{}; i < size; ++i)
	{
		b[i] = rand();
	}
	return b;
}


int main()
{
	//int number{ 42 };
	//DoubleNumber(number);
	//DoubleNumber(10);
	//PrintDouble(number);
	//PrintDouble(10);

	//Blob b1{ 10 };
	//Blob b2{ b1 };

	//DoubleNumber(b1);




	//std::cout << '\n';
	//std::cout << '\n';
	//b2 = b1;
	//b1 = Blob{ 6 };
	//std::cout << '\n';

	////b1.Print();
	////b2.Print();
	//std::cout << '\n';
	//std::cout << '\n';
	//std::cout << '\n';

	//Blob b3{ MakeBlob(10)}; // ask for help in class
	//std::cout << '\n';
	//std::cout << '\n';
	//b3 = MakeBlob(4);


	std::vector<Blob> blobs;
	//blobs.resize(15); // doesnt work because you dont have a default constructor
	blobs.reserve(15); //creates a new array. use reserve instead of resize
	blobs.push_back(Blob{ 4 });
	blobs.push_back(Blob{ 4 });
	blobs.push_back(Blob{ 4 });
	blobs.push_back(Blob{ 4 });
	blobs.push_back(Blob{ 4 });
	blobs.push_back(Blob{ 4 });
	blobs.push_back(Blob{ 4 });
	blobs.push_back(Blob{ 4 });

	std::cout << '\n';
	std::cout << '\n';

}









//void StartHeapControl();
//void PrintInteger(int& i);
//void PrintInteger(const int& i);
//void PrintInteger(int&& i);
//
//void PrintBlob(const Blob& b);
//
//void TestBlob();
//
//Blob CreateBlob1(int size);
//Blob CreateBlob2(int size);
//
//
//
//int main()
//{
//	StartHeapControl();
//
//
//	TestBlob();
//}
//
//void PrintInteger(int& i)
//{
//	std::cout << "l-value reference, the integer is: " << i << '\n';
//}
//
//void PrintInteger(const int&i)
//{
//	std::cout << "const l-value reference, the integer is: " << i << '\n';
//}
//
//void PrintInteger(int&& i)
//{
//	std::cout << "r-value reference, the integer is: " << i << '\n';
//}
//
//void TestBlob()
//{
//	Blob b1{ 10 };
//	// first without move semantics
//
//	std::cout << "Leaving TestBlob.\n\n";
//
//}
//
//Blob CreateBlob1(int size)
//{
//	Blob b{ size };
//	return b; //return a l value
//}
//
//Blob CreateBlob2(int size)
//{
//	return Blob{ size }; // return a prvalue
//}
//
//
//void PrintBlob(const Blob& b)
//{
//	std::cout << "Blob" << b << '\n';
//}
//
//void StartHeapControl()
//{
//#if defined(DEBUG) | defined(_DEBUG)
//	// Notify user if heap is corrupt
//	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
//
//	// Report detected leaks when the program exits
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//
//	// Set a breakpoint on the specified object allocation order number
//	//_CrtSetBreakAlloc( 143 );
//#endif
//}