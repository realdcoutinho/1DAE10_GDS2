#pragma once
#include "utils.h"
#include <vector>

class Platform
{
public:
	explicit Platform(Point2f bottomLeft);
	Platform(const Platform& other) = delete; //copy constructor
	Platform& operator=(const Platform& other) = delete; // assignment operator
	Platform(Platform&& other) = delete; // move constructor
	Platform& operator=(Platform&& other) = delete; // move assignment operator
	virtual void Draw() const;

protected:
	Point2f m_BottomLeft;
};


