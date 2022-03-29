#include "Blob.h"

Blob::Blob(int size)
	: m_Size{ size }
	, m_pData{ new int[size] {} }
{
	//std::cout << "Constructor, size = " << size << "\n";
	//for (int i = 0; i < m_Size; i++)
	//{
	//	m_pData[i] = rand() % 100;
	//}

	std::cout << "Blob ctor" << '\n';
	for (int i{}; i < m_Size; i++)
	{
		m_pData[i] = i;
	}
}

Blob::~Blob()
{
	std::cout << "Destructor\n";
	delete[] m_pData;
	//m_pData = nullptr;
}

Blob::Blob(const Blob & other) 
	:m_Size{ other.m_Size }
	, m_pData{ new int[other.m_Size]{} }
{
	std::cout << "Copy constructor\n";
	for (int i = 0; i < m_Size; ++i)
	{
		m_pData[i] = other.m_pData[i];
	}
}

Blob& Blob::operator=(const Blob& rhs)
{
	if (&rhs != this)
	{
		std::cout << "Copy assignment\n";
		m_Size = rhs.m_Size;
		delete[] m_pData;
		m_pData = new int[rhs.m_Size];
		for (int i = 0; i < m_Size; ++i)
		{
			m_pData[i] = rhs.m_pData[i];
		}
	}
	return *this;
}

Blob::Blob(Blob&& other) noexcept
	:m_Size{ other.m_Size }
	, m_pData{ other.m_pData }
{
	std::cout << "move constructor\n";
	other.m_Size = 0;
	other.m_pData = nullptr;
}

Blob& Blob::operator=(Blob&& rhs) noexcept
{
	if (&rhs != this)
	{
		std::cout << "Move Assignemnt\n";
		delete[] m_pData;
		m_pData = rhs.m_pData;
		m_Size = rhs.m_Size;
		rhs.m_pData = nullptr;
		rhs.m_Size = 0;
	}
	return *this;
}

void Blob::Print() const
{
	for (int i{}; i < m_Size; i++)
	{
		std::cout << m_pData[i] << ' ';
	}
	std::cout << '\n';
}

void Blob::Double()
{
	for (int i{}; i < m_Size; i++)
	{
		m_pData[i] *= 2;
	}
}

int& Blob::operator[](int index)
{
	return m_pData[index];
}

std::ostream & operator<<(std::ostream & out, const Blob & rhs)
{
	out << "Size = " << rhs.m_Size << "\tData: 0x" << rhs.m_pData << " ";
	for (int i = 0; i < rhs.m_Size; ++i)
	{
		out << rhs.m_pData[i] << ", ";
	}

	return out;
}

