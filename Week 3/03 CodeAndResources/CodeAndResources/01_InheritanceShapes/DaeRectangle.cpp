#include "pch.h"		
#include "DaeRectangle.h"
#include "utils.h"

DaeRectangle::DaeRectangle( const Point2f &center, float width, float height, const Color4f &color )
: m_Center{ center }
, m_Width{ width }
, m_Height{ height }
, m_Color{ color }
{
}

void DaeRectangle::Draw( ) const
{
	utils::SetColor( m_Color );
	utils::FillRect( Point2f{ m_Center.x - m_Width / 2,m_Center.y - m_Height / 2 }, m_Width, m_Height );
}

void DaeRectangle::Translate( const Vector2f& tr )
{
	m_Center += tr;
}
