#include "pch.h"
#include "PowerUp.h"
#include "Texture.h"
#include "utils.h"
#include <iostream>

PowerUp::PowerUp(const Point2f& center, PowerUp::Type type)
	: m_pTexture{ new Texture{"./resources/Images/PowerUp.png" } },
	m_RotSpeed{ 50 }, m_Type{ type }, m_Angle{ 0.0f }
{
	if (!(m_pTexture->IsCreationOk()))
	{
		std::cout << "Error loading PowerUp texture." << std::endl;
	}
	GetWidth();
	GetHeight();
	m_Shape = Circlef{ center, m_TextureWidth / 2 };
}

PowerUp::~PowerUp()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void PowerUp::Update(float elapsedSec)
{
	m_Angle += m_RotSpeed * elapsedSec;
	if (m_Angle > 360)
		m_Angle = 0;
}
void PowerUp::Draw() //const
{
	m_TextClip.left = 0.0f;
	m_TextClip.bottom = m_TextureHeight / 2 * (int)m_Type;
	m_TextClip.width = m_TextureWidth;
	m_TextClip.height = m_TextureHeight/2;

	Rectf destination{ m_Shape.center.x - m_Shape.radius, m_Shape.center.y - m_Shape.radius, m_TextureWidth, m_TextureHeight/2 };

	glPushMatrix();
	glTranslatef(m_Shape.center.x, m_Shape.center.y, 0);
	glRotatef(m_Angle, 0, 0, 1);
	glTranslatef(-m_Shape.center.x, -m_Shape.center.y, 0);
	m_pTexture->Draw(destination, m_TextClip);
	glPopMatrix();

}

bool PowerUp::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}

float PowerUp::GetWidth() 
{
	m_TextureWidth = m_pTexture->GetWidth();
	return m_TextureWidth;
}

float PowerUp::GetHeight()
{
	m_TextureHeight = m_pTexture->GetHeight();
	return m_TextureHeight;
}
