#include "pch.h"		
#include "DaeCircle.h"
#include "utils.h"
#include <iostream>


DaeCircle::DaeCircle( const Point2f &center, float diameter, const Color4f &color, bool isFilled )
: DaeEllipse{ center, diameter , diameter , color , isFilled }
{
	std::cout << "Circle was created" << '\n';
}


std::string DaeCircle::ToString() const
{
	std::string string{ "<DaeCircle \n" };
	string += DaeShape::PropertiesToString();
	string += "/>\n\n";
	return string;
}