#include "pch.h"
#include "Health.h"

Health::Health( int value) 
	: m_Value{value}
{
}
int Health::GetValue( ) const
{
	return m_Value;
}

Health& Health::operator+=(int rhs)
{
	m_Value += rhs;
	return *this;
}

Health& Health::operator-=(int rhs)
{
	m_Value -= rhs;
	return *this;
}

Health operator+(int lhs, const Health& rhs)
{
	int temp{ lhs + rhs.GetValue() };
	Health* value{ new Health(temp) };
	return *value;
}

Health operator-(int lhs, const Health& rhs)
{
	int temp{ lhs - rhs.GetValue() };
	Health* value{ new Health(temp) };
	return *value;
}

Health operator+(const Health& lhs, int rhs)
{
	int temp{ lhs.GetValue() + rhs };
	Health* value{ new Health(temp) };
	return *value;
}

Health operator-(const Health& lhs, int rhs)
{
	int temp{ lhs.GetValue() - rhs};
	Health* value{ new Health(temp) };
	return *value;
}