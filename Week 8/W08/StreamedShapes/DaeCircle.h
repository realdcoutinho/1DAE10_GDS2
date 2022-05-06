#pragma once
#include "Vector2f.h"

//mine
#include "DaeEllipse.h"

class DaeCircle final : public DaeEllipse
{
public:
	DaeCircle( const Point2f& center, float diameter, const Color4f& color, bool isFilled ); 
	std::string ToString() const;
};

 
