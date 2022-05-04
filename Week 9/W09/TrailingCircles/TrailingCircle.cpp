#include "pch.h"
#include <cmath>
#include "TrailingCircle.h"
#include "utils.h"


TrailingCircle::TrailingCircle( float radius, const Point2f& center )
	: m_Radius{ radius } 
	, m_Center{center}
	, m_Color{ GetRandomColor() }
	, m_Velocity(GetRandomVelocity() )
	, m_NrTrails{15}
	, m_TimeMax{0.08f}
	, m_CurrentTime{}
{
}

void TrailingCircle::Update( float elapsedSec, const Rectf& boundingRect )
{
	// Calculate new position
	Vector2f centerVector{ m_Center };
	centerVector += m_Velocity * elapsedSec;
	m_Center = centerVector.ToPoint2f( );

	//Update deque
	UpdateDeque(elapsedSec);

	// Handle reflection against bounding rectangle
	if ( m_Velocity.x > 0 && m_Center.x + m_Radius > boundingRect.left + boundingRect.width )
	{
		m_Velocity.x = -m_Velocity.x;
	}
	else if ( m_Velocity.x < 0 && m_Center.x - m_Radius < boundingRect.left )
	{
		m_Velocity.x = -m_Velocity.x;
	}
	if ( m_Velocity.y > 0 && m_Center.y + m_Radius > boundingRect.bottom + boundingRect.height )
	{
		m_Velocity.y = -m_Velocity.y;
	}
	else if ( m_Velocity.y < 0 && m_Center.y - m_Radius < boundingRect.bottom )
	{
		m_Velocity.y = -m_Velocity.y;
	}
}

void TrailingCircle::Draw( ) const
{
	utils::SetColor( m_Color );
	utils::FillEllipse( m_Center, m_Radius, m_Radius );
	DrawDeque();
}

Vector2f TrailingCircle::GetRandomVelocity( )
{
	const int speedMin{ 50 };
	const int speedMax{ 100 };
	int speed{ rand( ) % ( speedMax - speedMin + 1 ) + speedMin };
	float angle{ rand( ) % 360 * float(utils::g_Pi / 360) };
	return Vector2f{ speed * cos( angle ) , speed * sin( angle ) };
}

Color4f TrailingCircle::GetRandomColor( )
{
	return Color4f{ rand( ) % 256 / 256.0f, rand( ) % 256 / 256.0f, rand( ) % 256 / 256.0f, 1.0f };
}


void TrailingCircle::UpdateDeque(float elapsedSec)
{
	m_CurrentTime += elapsedSec;
	if (m_CurrentTime >= m_TimeMax)
	{
		m_Positions.push_back(m_Center);
		m_CurrentTime = 0;
	}
	if (m_Positions.size() > m_NrTrails - 1)
	{
		m_Positions.pop_front();
	}
}

void TrailingCircle::DrawDeque() const
{
	float j{};
	for (int i{}; i < m_Positions.size(); ++i)
	{
		j += 1.f / static_cast<float>(m_NrTrails);
		utils::SetColor(Color4f(m_Color.r, m_Color.g, m_Color.b, m_Color.a * j));
		utils::FillEllipse(m_Positions[i], m_Radius *j, m_Radius*j);
	}
}