#include "pch.h"		
#include "DaeRectLabel.h"
#include "utils.h"

DaeRectLabel::DaeRectLabel( const Point2f& center, float width, float height, const Color4f& color, const std::string& label, const Color4f& textColor, TTF_Font* pFont )
: m_Center{ center }
, m_Width{ width }
, m_Height{ height }
, m_Color{ color }
, m_pLabelText{ new Texture(label, pFont, textColor) }
{
	m_MarginX = ( m_Width - m_pLabelText->GetWidth( ) ) / 2;
	m_MarginY = ( m_Height - m_pLabelText->GetHeight( ) ) / 2;
}

DaeRectLabel::~DaeRectLabel( )
{
	delete m_pLabelText;
	m_pLabelText = nullptr;
}

void DaeRectLabel::Draw( ) const
{
	// Rectangle
	utils::SetColor( m_Color );
	utils::FillRect( Point2f{ m_Center.x - m_Width / 2,m_Center.y - m_Height / 2 }, m_Width, m_Height );

	// Label
	Point2f bottomLeft{ m_Center.x - m_Width / 2 + m_MarginX, m_Center.y - m_Height / 2 + m_MarginY };
	m_pLabelText->Draw( bottomLeft );
}

void DaeRectLabel::Translate( const Vector2f& tr )
{
	m_Center += tr;
}

