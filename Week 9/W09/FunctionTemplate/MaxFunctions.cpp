#include "pch.h"
#include <array>
#include <vector>
#include <string>
#include <deque>
#include <list>
#include <iostream>
#include "MaxFunctions.h"

const Fraction& Max( const Fraction& a, const Fraction& b )
{
	return a < b ? b : a;
}
