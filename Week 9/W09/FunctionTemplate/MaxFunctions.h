#pragma once
#include <string>
#include "Fraction.h"

template <typename T>
T Max( T a, T b );
//float Max( float a, float b );
//const std::string& Max( const std::string& a, const std::string& b );
const Fraction& Max( const Fraction& a, const Fraction& b );

template <typename T>
T Max(T a, T b)
{
	return a < b ? b : a;
}

