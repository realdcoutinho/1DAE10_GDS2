#pragma once
#include <iostream>

template <typename T>
class DataHolder
{
private:
	T m_Data{};
public:
	T GetData() const;
	void SetData(const T& data);
	void Print() const;
};

template <typename T>
T DataHolder<T>::GetData() const
{
	return m_Data;
}

template <typename T>
void DataHolder<T>::SetData(const T& data)
{
	m_Data = data;
}

template <typename T>
void DataHolder<T>::Print() const
{
	std::cout << m_Data << '\n';
}