//#pragma once
//#include "Vector2f.h"
//
//class DaeRectangle 
//{
//public:
//	DaeRectangle( const Point2f& center, float width, float height, const Color4f& color );
//
//	void Draw( ) const;
//	void Translate( const Vector2f& tr );
//
//protected: 
//	Point2f m_Center;
//	float m_Width;
//	float m_Height;
//private:
//	Color4f m_Color;
//};

#pragma once
#include "Vector2f.h"
#include "DaeShape.h"

class DaeRectangle : public DaeShape
{
public:
	DaeRectangle(const Point2f& center, float width, float height, const Color4f& color);

	void Draw() const;
private:
	Color4f m_Color;
};
