#pragma once
#include <iostream>

class IntHolder
{
private:
	int m_Data{};
public:
	int GetData() const;
	void SetData(const int& data);
	void Print() const;
};

int IntHolder::GetData() const
{
	return m_Data;
}

void IntHolder::SetData(const int& data)
{
	m_Data = data;
}

void IntHolder::Print() const
{
	std::cout << m_Data << '\n';
}