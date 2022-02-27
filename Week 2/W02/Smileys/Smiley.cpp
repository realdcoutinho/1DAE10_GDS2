// -- Smiley.cpp file --
// Decide yourself about the necessary include directives
#include "pch.h"
#include "Smiley.h"
#include <iostream>
#include "Texture.h"
// ....

// Static Texture data
Texture* Smiley::m_pSmileyTexture{ nullptr };
int Smiley::m_InstanceCounter{ 0 };

// Constructor
// Initializes the object, among others:
//	- Initializes the data members, the velocity gets a random value within the inclusive range[60, 180] and [-180, -60]
//	- Creates a texture object to load the image, only if it hasn’t been created before( !)
//  - Adapts the instance counter
Smiley::Smiley(const Point2f& position, Vector2f velocity)
	: m_Position{position}
	, m_Velocity{ velocity }
{
	++m_InstanceCounter;
	std::cout << "Constructor was built. You have " << m_InstanceCounter << " instances!" << '\n';
	CreateTextures();
}

// Destructor
// Deletes the Texture object when this is the last Smiley that is being destroyed.
Smiley::~Smiley( )
{
	//delete m_pSmileyTexture;
	//m_pSmileyTexture = nullptr;
	std::cout << "We are deleting Instance number: " << m_InstanceCounter << '\n';
	--m_InstanceCounter;
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

	Rectf souceRect{ m_TextureWidth, 0, m_TextureWidth , m_TextureHeight };
	if (m_Position.x > 846.f) {
		m_Position.x = m_Position.x - m_TextureWidth / 4;
		m_pSmileyTexture->Draw(m_Position, souceRect);
	}
	else {
		m_pSmileyTexture->Draw(m_Position, souceRect);
	}
}

// Update
// - When the smiley is not sleeping, the new position - using the velocity and elapsed seconds - is calculated.
// - The velocity changes sign when at this new position the smiley is outside the bounding rectangle (boundingRect)
// - Checks whether at this new position, it is located in the safe area and updates m_IsInSafeArea accordingly.
void Smiley::Update( float elapsedSec, const Rectf& boundingRect, const Rectf& safeRect )
{
	const float bLeft{ boundingRect.left };
	const float bBottom{ boundingRect.bottom };
	const float bRight{ boundingRect.left + boundingRect.width };
	const float bTop{ boundingRect.bottom + boundingRect.height };


	//m_Position.y = m_Velocity.y * elapsedSec;

	if (m_Position.x + m_TextureWidth/4 > bRight && m_Velocity.x > 0)
	{
		m_Position.x = -m_Velocity.x * elapsedSec;
	}
	if (m_Position.y + m_TextureHeight > bTop && m_Velocity.y > 0)
	{
		m_Position.y = -m_Velocity.y * elapsedSec;
	}
	if (m_Position.x < bLeft && m_Velocity.x < 0)
	{
		m_Position.x = m_Velocity.x * elapsedSec;
	}
	if (m_Position.y < bBottom && m_Velocity.y < 0)
	{
		m_Position.y = m_Velocity.y * elapsedSec;
	}

}

// HitTest
// If the value of the parameter pos is within the boundaries of the smiley’s circle,
// then the sleeping state of the smiley changes.
void Smiley::HitTest( const Point2f& pos )
{
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
}

// IncreaseSpeed
// Changes the speed 5% up
void Smiley::IncreaseSpeed( )
{
}

// DecreaseSpeed
// Changes the speed 5% down
void Smiley::DecreaseSpeed( )
{
}

// IsInSafeArea
// Returns true when the smiley is completely inside the safe area as indicated by safeRect
bool Smiley::IsInSafeArea( const Rectf& safeRect )
{
	return true; // change this later
}

void Smiley::DeleteSmileys()
{

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