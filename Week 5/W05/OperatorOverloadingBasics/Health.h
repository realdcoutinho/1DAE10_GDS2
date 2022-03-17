#pragma once

class Health final
{
public:
	Health( int value); 
	int GetValue( ) const;

	Health& operator+=(int rhs);
	Health& operator-=(int rhs);
	friend Health operator+(int lhs, const Health& rhs);
	friend Health operator-(int lhs, const Health& rhs);

	friend Health operator+(const Health& lhs, int rhs);
	friend Health operator-(const Health& lhs, int rhs);
	

private:
	int m_Value;
};

Health operator+(int lhs, const Health& rhs);
Health operator-(int lhs, const Health& rhs);

Health operator+(const Health& lhs, int rhs);
Health operator-(const Health& lhs, int rhs);