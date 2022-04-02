#include "pch.h"
#include "Sprite.h"
#include <iostream>
#include "Texture.h"

Sprite::Sprite( const std::string& path, int cols, int rows, float frameSec )
	: m_Cols( cols )
	, m_Rows( rows )
	, m_FrameSec( frameSec )
	, m_AccuSec{}
	, m_ActFrame{}
	, m_pTexture{ new Texture( path ) }
	, m_FilePath{path}
{
	//m_pTexture = new Texture( path );
}

Sprite::~Sprite( )
{
	 //m_pTexture = nullptr;
	 delete m_pTexture;
}

Sprite::Sprite(const Sprite& rhs) //copy constructor
	: m_Cols(rhs.m_Cols)
	, m_Rows(rhs.m_Rows)
	, m_FrameSec(rhs.m_FrameSec)
	, m_AccuSec{rhs.m_AccuSec}
	, m_ActFrame{rhs.m_ActFrame}
	, m_pTexture{ new Texture{ rhs.m_FilePath } }
{
	std::cout << "Copy Constructor" << '\n';
}

Sprite& Sprite::operator=(const Sprite& rhs) //copy assignment operator
{
	if (&rhs != this)
	{
		m_Cols = rhs.m_Cols;
		m_Rows = rhs.m_Rows;
		m_FrameSec = rhs.m_FrameSec;
		m_AccuSec = rhs.m_AccuSec;
		m_ActFrame = rhs.m_ActFrame;
		m_FilePath = rhs.m_FilePath;
		delete m_pTexture;
		m_pTexture =  new Texture{ rhs.m_FilePath };
	}
	return *this;
}

Sprite::Sprite(Sprite&& rhs) noexcept // move constructor
	: m_Cols(rhs.m_Cols)
	, m_Rows(rhs.m_Rows)
	, m_FrameSec(rhs.m_FrameSec)
	, m_AccuSec{ rhs.m_AccuSec }
	, m_ActFrame{ rhs.m_ActFrame }
	, m_pTexture{ rhs.m_pTexture }
{
	rhs.m_Cols = 0;
	rhs.m_Rows = 0;
	rhs.m_FrameSec = 0;
	rhs.m_AccuSec = 0;
	rhs.m_ActFrame = 0;
	//rhs.m_pTexture = nullptr;
	rhs.m_pTexture = nullptr;
	std::cout << "Move Constructor" << '\n';
}

Sprite& Sprite::operator=(Sprite&& rhs) noexcept //Move Assignment Operator
{
	if (&rhs != this)
	{
		m_Cols = rhs.m_Cols;
		m_Rows = rhs.m_Rows;
		m_FrameSec = rhs.m_FrameSec;
		m_AccuSec = rhs.m_AccuSec;
		m_ActFrame = rhs.m_ActFrame;
		delete m_pTexture;

		m_pTexture = rhs.m_pTexture;
		rhs.m_Cols = 0;
		rhs.m_Rows = 0;
		rhs.m_FrameSec = 0;
		rhs.m_AccuSec = 0;
		rhs.m_ActFrame = 0;
		//rhs.m_pTexture = nullptr;
		rhs.m_pTexture = nullptr;
		std::cout << "Move Assignment Operator" << '\n';
	}
	return *this;

}



void Sprite::Update( float elapsedSec )
{
	m_AccuSec += elapsedSec;

	if ( m_AccuSec > m_FrameSec )
	{
		// Go to next frame
		++m_ActFrame;
		if ( m_ActFrame >= m_Cols * m_Rows )
		{
			m_ActFrame = 0;
		}

		// Only keep the remaining time
		m_AccuSec -= m_FrameSec;
	}
}

void Sprite::Draw( const Point2f& pos, float scale ) const
{
	// frame dimensions
	const float frameWidth{  m_pTexture->GetWidth() / m_Cols };
	const float frameHeight{  m_pTexture->GetHeight() / m_Rows };
	int row = m_ActFrame / m_Cols;
	int col = m_ActFrame % m_Cols;

	Rectf srcRect;
	srcRect.height = frameHeight;
	srcRect.width = frameWidth;
	srcRect.left = m_ActFrame % m_Cols * srcRect.width;
	srcRect.bottom = m_ActFrame / m_Cols * srcRect.height + srcRect.height;
	Rectf destRect{ pos.x, pos.y,srcRect.width * scale,srcRect.height * scale };
	m_pTexture->Draw( destRect, srcRect );
}

float Sprite::GetFrameWidth( )
{
	return m_pTexture->GetWidth( ) / m_Cols;
}

float Sprite::GetFrameHeight( )
{
	return m_pTexture->GetHeight( ) / m_Rows;
}

