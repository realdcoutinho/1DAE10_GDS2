#include "pch.h"
#include "Container.h"
#include <iostream>

Container::Container(int capacity)
	: m_Size{}
	, m_Capacity{ capacity }
	, m_pElement{ new int[capacity] }
{
	std::cout << "Constructor: Container( int capacity ), creates resources";
}

Container::~Container() 
{
	delete[] m_pElement;
	std::cout << "Container destructor: release the resources\n";
}

int Container::Size() const
{
	return m_Size;
}

int Container::Capacity() const
{
	return m_Capacity;
}

int Container::Get(int index) const
{
	return m_pElement[index];
}

void Container::Set(int index, int newValue)
{
	m_pElement[index] = newValue;
}

void Container::PushBack(int element)
{
	if (m_Size == m_Capacity) {
		Reserve(m_Capacity * 2 + 1);
	}
	m_pElement[m_Size] = element;
	m_Size += 1;
}

void Container::Reserve(int newCapacity)
{
	int *tempArray= new int[newCapacity];

	for (int i{}; i < m_Size; ++i)
	{
		tempArray[i] = m_pElement[i];
	}

	delete[] m_pElement;
	m_Capacity = newCapacity;
	m_pElement = tempArray;
}