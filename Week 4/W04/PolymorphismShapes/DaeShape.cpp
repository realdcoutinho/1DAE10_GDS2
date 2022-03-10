#include "pch.h"
#include "DaeShape.h"
#include "utils.h"
#include <iostream>

DaeShape::DaeShape(const Point2f& center, float width, float height, const Color4f& color)
	: m_Center{ center }
	, m_Width{ width }
	, m_Height{ height }
	, m_Color{ color }
{
	std::cout << "Shape was created" << '\n';
}

void DaeShape::Translate(const Vector2f& tr) 
{
	m_Center += tr;
}