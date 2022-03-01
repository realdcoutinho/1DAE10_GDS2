// -- Smiley.cpp file --
// Decide yourself about the necessary include directives
#include "pch.h"
#include "Smiley.h"
#include <iostream>
#include "Texture.h"
using namespace utils;

// Static Texture data
Texture* Smiley::m_pSmileyTexture{ nullptr };
int Smiley::m_InstanceCounter{ 0 };

// Constructor
// Initializes the object, among others:
//	- Initializes the data members, the velocity gets a random value within the inclusive range[60, 180] and [-180, -60]
//	- Creates a texture object to load the image, only if it hasn’t been created before( !)
//  - Adapts the instance counter
Smiley::Smiley(const Point2f& position)
	: m_Position{position}
{
	++m_InstanceCounter;
	std::cout << "Constructor was built. You have " << m_InstanceCounter << " instances!" << '\n';
	SetVelocity();
	CreateTextures();
}

// Destructor
// Deletes the Texture object when this is the last Smiley that is being destroyed.
Smiley::~Smiley( )
{
	std::cout << "We are deleting Instance number: " << m_InstanceCounter << '\n';
	--m_InstanceCounter;
	DeleteSmileys();
}

void Smiley::SetVelocity()
{
	m_VelocityZero = { 0,0 };

	float velocityX = float(60 + (std::rand() % (180 - 60 + 1)));
	float velocityY = float(60 + (std::rand() % (180 - 60 + 1)));

	if (m_InstanceCounter % 2 == 0) {
		m_Velocity = { velocityX , velocityY };
	}
	if (m_InstanceCounter % 2 != 0) {
		m_Velocity = { -velocityX , -velocityY };
	}
}

// Draw
// Draws a part of the image on the window, which part depends on the state of the smiley:
// - If the smiley is sleeping then the sleeping smiley is drawn.
// - If the smiley is at the highest position, then the happy smiley is drawn.
// - If the smiley is not in the safe area, the scary smiley is drawn.
// - If none of the above conditions is met, the neutral smiley should be drawn.
void Smiley::Draw( )
{
	float numberOfStates{ 4 };
	Rectf souceRect{ 0, 0, m_TextureWidth , m_TextureHeight };

	switch (m_State)
	{
		case int(Smiley::State::happy) :
		souceRect.left += int(Smiley::State::happy);
		m_pSmileyTexture->Draw(m_Position, souceRect);
		break;
	case int(Smiley::State::neutral):
		souceRect.left += m_TextureWidth * int(Smiley::State::neutral);
		m_pSmileyTexture->Draw(m_Position, souceRect);
		break;
	case int(Smiley::State::angry) :
		souceRect.left += m_TextureWidth * int(Smiley::State::angry);
		m_pSmileyTexture->Draw(m_Position, souceRect);
		break;
	case int(Smiley::State::sleepy):
		souceRect.left += m_TextureWidth * int(Smiley::State::sleepy);
		m_pSmileyTexture->Draw(m_Position, souceRect);
		break;
	}
}

// Update
// - When the smiley is not sleeping, the new position - using the velocity and elapsed seconds - is calculated.
// - The velocity changes sign when at this new position the smiley is outside the bounding rectangle (boundingRect)
// - Checks whether at this new position, it is located in the safe area and updates m_IsInSafeArea accordingly.
void Smiley::Update( float elapsedSec, const Rectf& boundingRect, const Rectf& safeRect )
{
	BoundingEdges(boundingRect, elapsedSec);
	IsInSafeArea(safeRect);
	SetState(safeRect);
}

// HitTest
// If the value of the parameter pos is within the boundaries of the smiley’s circle,
// then the sleeping state of the smiley changes.
void Smiley::HitTest( const Point2f& pos )
{
	Rectf smile{ m_Position.x, m_Position.y, m_TextureWidth, m_TextureHeight };

	bool isHit{ IsPointInRect(pos, smile) };

	if (isHit && m_State != int(Smiley::State::sleepy))
	{
		m_IsSleeping = true;
		m_CurrentVelocity = m_Velocity;
		m_Velocity = m_VelocityZero;
		isHit = false;
	}
	if (isHit && m_State == int(Smiley::State::sleepy))
	{
		m_IsSleeping = false;
		m_Velocity = m_CurrentVelocity;
		isHit = false;
		//switch (m_State)
		//{
		//	case int(Smiley::State::happy) :
		//		m_IsSleeping = true;
		//		m_Velocity.x = 0;
		//		m_Velocity.y = 0;
		//		isHit = false;
		//	break;
		//	case int(Smiley::State::neutral) :
		//		m_IsSleeping = true;
		//		m_Velocity.x = 0;
		//		m_Velocity.y = 0;
		//		isHit = false;
		//	break;
		//	case int(Smiley::State::angry) :
		//		m_IsSleeping = true;
		//		m_Velocity.x = 0;
		//		m_Velocity.y = 0;
		//		isHit = false;
		//	break;
		//	case int(Smiley::State::sleepy) :
		//		m_IsSleeping = false;
		//		m_Velocity.x = 100;
		//		m_Velocity.y = 100;
		//		isHit = false;
		//	break;
		//}
	}
}

// IsSleeping
// Getter of the m_IsSleeping data member
bool Smiley::IsSleeping( )
{
	return m_IsSleeping; 
}

// GetPosition
// Getter of the m_Position data member
Point2f Smiley::GetPosition( )
{
	return m_Position;
}

// SetHighest
// Setter of the m_IsHighest data member
void Smiley::SetHighest( bool isHighest )
{
	m_IsHighest = isHighest;
}

// IncreaseSpeed
// Changes the speed 5% up
void Smiley::IncreaseSpeed( )
{
	float increment{ 0.05f };
	m_Velocity.x += m_Velocity.x * increment;
	m_Velocity.y += m_Velocity.y * increment;
}

// DecreaseSpeed
// Changes the speed 5% down
void Smiley::DecreaseSpeed( )
{
	float decrement{ 0.05f };
	m_Velocity.x -= m_Velocity.x * decrement;
	m_Velocity.y -= m_Velocity.y * decrement;
}

// IsInSafeArea
// Returns true when the smiley is completely inside the safe area as indicated by safeRect


void Smiley::DeleteSmileys()
{
	delete m_pSmileyTexture;
	m_pSmileyTexture = nullptr;
}


void Smiley::CreateTextures()
{
	float numberOfStates{ 4 };

	m_pSmileyTexture = new Texture("Textures/Smileys.png");
	
	m_TextureHeight = m_pSmileyTexture->GetHeight();
	m_TextureWidth = m_pSmileyTexture->GetWidth() / numberOfStates;
}

float Smiley::GetWidth() const
{
	return m_TextureWidth;
}
float Smiley::GetHeight() const
{
	return m_TextureHeight;
}

void Smiley::BoundingEdges(const Rectf& boundingRect, float elapsedSec)
{
	Rectf bounding{ boundingRect.left, boundingRect.bottom, 
		boundingRect.left + boundingRect.width, boundingRect.bottom + boundingRect.height };

	m_Position.x += m_Velocity.x * elapsedSec;
	m_Position.y += m_Velocity.y * elapsedSec;

	if (m_Position.x + m_TextureWidth > bounding.width)
	{
		m_Velocity.x *= -1;
	}
	if (m_Position.y + m_TextureHeight > bounding.height)
	{
		m_Velocity.y *= -1;
	}
	if (m_Position.x < bounding.left && m_Velocity.x < 0)
	{
		m_Velocity.x *= -1;
	}
	if (m_Position.y < bounding.bottom && m_Velocity.y < 0)
	{
		m_Velocity.y *= -1;
	}
}

bool Smiley::IsInSafeArea(const Rectf& safeRect)
{
	if (m_Position.x + m_TextureWidth >= safeRect.left + safeRect.width)
	{
		return false;
	}
	if (m_Position.y + m_TextureHeight >= safeRect.bottom + safeRect.height)
	{
		return false;
	}
	if (m_Position.x < safeRect.left)
	{
		return false;
	}
	if (m_Position.y < safeRect.bottom)
	{
		return false;
	}
	else {
		return true;
	}
}

void Smiley::SetState(const Rectf& safeRect)
{
	bool isSafe{ IsInSafeArea(safeRect) };

	if (m_IsHighest && !(m_IsSleeping))
	{
		m_State = int(Smiley::State::happy);
		std::cout << "Im the higest" << '\n';
	}
	else 
	{
		if (isSafe)
		{
			m_State = int(Smiley::State::neutral);
		}
		else
		{
			m_State = int(Smiley::State::angry);
		}
		if (m_IsSleeping)
		{
			m_State = int(Smiley::State::sleepy);
		}
		else
		{
			if (isSafe)
			{
				m_State = int(Smiley::State::neutral);
			}
			else
			{
				m_State = int(Smiley::State::angry);
			}
		}

	}
}