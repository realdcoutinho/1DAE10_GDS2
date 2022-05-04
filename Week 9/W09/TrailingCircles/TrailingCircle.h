#pragma once
#include "Vector2f.h"
#include <deque>


class TrailingCircle
{
public:
	TrailingCircle( float radius, const Point2f& center);
	void Update( float elapsedSec, const Rectf& boundingRect );
	void Draw( ) const;

private:

	std::deque<Point2f> m_Positions;
	size_t m_NrTrails;
	float m_TimeMax;
	float m_CurrentTime;

	const float m_Radius;
	const Color4f m_Color;
	Point2f m_Center;
	Vector2f m_Velocity;

	Vector2f GetRandomVelocity( );
	Color4f GetRandomColor( );

	void UpdateDeque(float elapsedSec);
	void DrawDeque() const;
};
