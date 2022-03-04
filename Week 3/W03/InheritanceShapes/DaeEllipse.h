#pragma once
#include "Vector2f.h"

#include "DaeShape.h"

class DaeEllipse  : public DaeShape
{
public:
	DaeEllipse( const Point2f& center, float width, float height, const Color4f& color, bool isFilled );

	void Draw( ) const;
private: 
	bool m_IsFilled;
};

 
