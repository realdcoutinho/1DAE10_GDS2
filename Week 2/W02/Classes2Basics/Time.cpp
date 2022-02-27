#include "pch.h"
#include <iostream>
#include <iomanip>
#include "Time.h"
#include <string> 

int Time::m_NrInstances{};

Time::Time( int seconds )
	: Time {seconds, 0, 0}
{
}
Time::Time(int seconds, int minutes)
	: Time{ seconds, minutes, 0 }
{
}

Time::Time( int seconds, int minutes, int hours ) : m_Seconds{ seconds + 60 * minutes  + 3600 * hours}
{
	++m_NrInstances;
	std::cout << "Created the Time number:" << m_NrInstances << '\n';
}

Time::~Time()
{
	std::cout << "Time destructor: release the resources\n";
	std::cout << "It was destryed the Time number: " <<  m_NrInstances << '\n';
	--m_NrInstances;
}

void Time::Print( ) const
{
	int hours{ m_Seconds / 3600 };
	int minutes{ m_Seconds % 3600 / 60 };
	int seconds{ m_Seconds % 3600 % 60 };
	std::cout << std::setw( 2 ) << std::setfill('0') << hours << ":";
	std::cout << std::setw( 2 ) << minutes << ":";
	std::cout << std::setw( 2 ) << seconds << std::endl;
}
int Time::GetSeconds( )
{
	return m_Seconds % 3600 % 60;
}
int Time::GetMinutes( )
{
	return m_Seconds % 3600 / 60;
}
int Time::GetHours( )
{
	return m_Seconds / 3600;
}

std::string Time::GetNrIntances()
{	

	std::string instances = std::to_string(m_NrInstances);
	return instances;
}


void Time::AddSeconds( int seconds )
{
	m_Seconds += seconds;
}
void Time::AddMinutes( int minutes )
{
	m_Seconds += minutes * 60;
}
void Time::AddHours( int hours )
{
	m_Seconds += hours * 3600;
}
