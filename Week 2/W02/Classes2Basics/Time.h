#pragma once
#include <string> 

class Time
{
public:
	Time( int seconds );
	Time( int seconds, int minutes );
	Time( int seconds, int minutes, int hours );
	~Time();


	void Print( ) const;
	int GetSeconds( );
	int GetMinutes( );
	int GetHours( );

	static std::string GetNrIntances();

	void AddSeconds( int seconds );
	void AddMinutes( int minutes );
	void AddHours( int hours );

private:
	int m_Seconds{};

	static int m_NrInstances;
};