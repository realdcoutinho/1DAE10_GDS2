#include "pch.h"
#include "Container.h"
#include <iostream>
#include <cassert>

Container::Container( int capacity ) 
	: m_Size{ 0 }
	, m_Capacity{ capacity }
	, m_pElement{ new int[capacity] }
{
	std::cout << "Constructor" << '\n';
}

Container::~Container( ) 
{ 
	delete[] m_pElement; 
	std::cout << "Destructor" << '\n';
}

Container::Container(Container&& rhs) noexcept
	: m_Size{rhs.m_Size}
	, m_Capacity{rhs.m_Capacity}
	, m_pElement{rhs.m_pElement}
{
	rhs.m_Size = 0;
	rhs.m_Capacity = 0;
	rhs.m_pElement = nullptr;
	std::cout << "Move Constructor" << '\n';
}

Container& Container::operator=(Container&& rhs) noexcept
{
	if (&rhs != this)
	{
		std::cout << "Move Assignemnt\n";
		delete[] m_pElement;
		m_pElement = rhs.m_pElement;
		m_Size = rhs.m_Size;
		m_Capacity = rhs.m_Capacity;
		rhs.m_pElement = nullptr;
		rhs.m_Capacity = 0;
		rhs.m_Size = 0;
	}
	return *this;
}



Container::Container(const Container& other) //copy constructor
	: m_Size{ other.m_Size }
	, m_Capacity{ other.m_Capacity }
	, m_pElement{ new int[other.m_Capacity] }
{
	for (int i{}; i < m_Size; ++i)
	{
		m_pElement[i] = other.m_pElement[i];
	}
	std::cout << "Copy Constructor" << '\n';
}

Container& Container::operator=(const Container& rhs) //assignment operator
{
	if (&rhs != this)
	{
		m_Size = rhs.m_Size;
		m_Capacity = rhs.m_Capacity;
		delete m_pElement;
		m_pElement = new int[rhs.m_Capacity];
		for (int i{}; i < m_Size; ++i)
		{
			m_pElement[i] = rhs.m_pElement[i];
		}
		std::cout << "Assignent Operator" << '\n';
	}
	else
	{
		//std::cout << "They are the same";
	}
	return *this;
}

int Container::Size( ) const
{ 
	return m_Size; 
}

int Container::Capacity( ) const
{
	return m_Capacity;
}

int Container::Get( int index ) const
{
	assert( index >= 0 && index < m_Size );
	return m_pElement[index];
}

void Container::Set( int index, int value )
{
	assert( index >= 0 && index < m_Size );
	m_pElement[index] = value;
}

void Container::PushBack( int value )
{
	if ( !( m_Size < m_Capacity ) )
	{
		Reserve( m_Capacity * 2  + 1);
	}
	m_pElement[m_Size] = value;
	++m_Size;
}

//int Container::operator[](int index) const
int& Container::operator[](int index) 
{
	assert(index >= 0 && index < m_Size);
	return m_pElement[index];
}

int Container::operator[](int index) const
{
	assert(index >= 0 && index < m_Size);
	return m_pElement[index];
}

void Container::Reserve( int newCapacity )
{
	if ( newCapacity <= m_Capacity )
	{
		return;
	}

	// Dynamically allocate memory
	int * pNew = new int[newCapacity] {};
	// Copy the elements into this new memory
	for ( int i{ 0 }; i < m_Size; ++i )
	{
		pNew[i] = m_pElement[i];
	}
	// Free the old memory
	delete[] m_pElement;

	// Adapt the data members to this new situation
	m_pElement = pNew;
	m_Capacity = newCapacity;
}



