#include "pch.h"		
#include "DaeRectLabel.h"
#include "utils.h"
#include <iostream>


DaeRectLabel::DaeRectLabel( const Point2f& center, float width, float height, const Color4f& color, const std::string& label, const Color4f& textColor, TTF_Font* pFont )
: DaeRectangle{ center , width, height, color}
, m_pLabelText{ new Texture(label, pFont, textColor) }
, m_ColorLabel{ color }
, m_Label{ label }
{
	m_MarginX = (width - m_pLabelText->GetWidth( ) ) / 2;
	m_MarginY = (height - m_pLabelText->GetHeight( ) ) / 2;
	std::cout << "label rect reacted" << '\n';
}

DaeRectLabel::~DaeRectLabel( )
{
	delete m_pLabelText;
	m_pLabelText = nullptr;
}

void DaeRectLabel::Draw( ) const
{
	DaeRectangle::Draw();
	Point2f bottomLeft{ DaeRectangle::m_Center.x - DaeRectangle::m_Width / 2 + m_MarginX, DaeRectangle::m_Center.y - DaeRectangle::m_Height / 2 + m_MarginY };
	m_pLabelText->Draw(bottomLeft);
}
std::string DaeRectLabel::ToString() const
{
	std::string string{ "<DaeRectLabel \n" };
	string += { DaeShape::PropertiesToString() };
	string += "TextColor=\"" + std::to_string(m_ColorLabel.r) + ',' + std::to_string(m_ColorLabel.g) + ',' + std::to_string(m_ColorLabel.g) + ',' + std::to_string(m_ColorLabel.a) + ',' + "\"" + "\n";
	string += "Label=\"" + m_Label + "\"" + "\n";
	string += "/>\n\n";
	return string;
}


