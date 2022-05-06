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

void DaeShape::Draw() const
{

}
void DaeShape::Translate(const Vector2f& tr) 
{
	m_Center += tr;
}

std::string DaeShape::PropertiesToString() const
{
	std::string toWrite{};

	toWrite += "Center=\"" + std::to_string(m_Center.x) + ',' + std::to_string(m_Center.y) + "\"" + "\n";
	toWrite += "Width=\"" + std::to_string(m_Width) + "\"" + "\n";
	toWrite += "Height\"" + std::to_string(m_Height) + "\"" + "\n";
	toWrite += "Color\"" + std::to_string(m_Color.r) + ',' + std::to_string(m_Color.g) + ',' + std::to_string(m_Color.g) + ',' + std::to_string(m_Color.a) + ',' + "\"" + "\n";

	return toWrite;
}