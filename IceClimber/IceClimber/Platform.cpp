#include "pch.h"
#include "Platform.h"
#include <iostream>

Platform::Platform(Point2f bottomLeft)
	: m_BottomLeft{bottomLeft}
{
	std::cout << "Platform was created" << '\n';
}

void Platform::Draw() const
{

}
