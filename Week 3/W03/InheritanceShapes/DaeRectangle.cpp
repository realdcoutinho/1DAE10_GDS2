#include "pch.h"		
#include "DaeRectangle.h"
#include "utils.h"

DaeRectangle::DaeRectangle(const Point2f& center, float width, float height, const Color4f& color)
	:DaeShape{ center, width, height, color }
{
}

void DaeRectangle::Draw() const
{
	utils::SetColor(DaeShape::m_Color);
	utils::FillRect(Point2f{ DaeShape::m_Center.x - DaeShape::m_Width / 2,DaeShape::m_Center.y - DaeShape::m_Height / 2 }, DaeShape::m_Width, DaeShape::m_Height);
}