#include "pch.h"
#include "Game.h"
#include <iostream>
using namespace utils;

Game::Game(const Window& window)
	:m_Window{ window }
{
	Initialize();

}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	InitializeVertices();
	CalculateSpeed();
	CalculateCenter();
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	RotateDiamond(elapsedSec);
}

void Game::Draw() const
{
	ClearBackground();

	DrawDiamond();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		break;
	case SDLK_RIGHT:
		//std::cout << "`Right arrow key released\n";
		break;
	case SDLK_1:
		break;
	case SDLK_KP_1:
		//std::cout << "Key 1 released\n";
		break;
	case SDLK_a:
		m_RotationDiretion = 1;
		break;
	case SDLK_d:
		m_RotationDiretion = -1;
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::InitializeVertices()
{
	Point2f p1{ 0, m_Height/2 };
	Point2f p2{ m_Width/2, 0 };
	Point2f p3{ m_Width, m_Height/2 };
	Point2f p4{ m_Width/2, m_Height };

	m_Vertices.push_back(p1);
	m_Vertices.push_back(p2);
	m_Vertices.push_back(p3);
	m_Vertices.push_back(p4);
	Rectf rect{ 0, 0, 200, 100 };
	m_Rect = rect;
}

void Game::DrawDiamond() const
{
	SetColor(Color4f(0.0f, 0.0f, 1.0f, 1.0f));
	glPushMatrix();
	//glTranslated(-m_DisplacementVector.x, -m_DisplacementVector.y, 1);
	//glTranslatef(-m_DisplacementVector.x, -m_DisplacementVector.y, 1);
	glRotatef(m_RotationAngle, 0, 0, 1);
	//glTranslatef(m_DisplacementVector.x, m_DisplacementVector.y, 1);
	//glTranslated(m_DisplacementVector.x, m_DisplacementVector.y, 1);
	//DrawRect(m_Rect);
	DrawPolygon(m_Vertices, true, 2.5f);
	glPopMatrix();
}

void Game::RotateDiamond(float elapsedSec)
{
	m_RotationAngle += m_RotationSpeed * elapsedSec * m_RotationDiretion;
}

void Game::CalculateSpeed()
{
	int speed{ rand() % 90 };
	m_RotationSpeed = float(speed);
}

void Game::CalculateCenter()
{
	m_Center.x = m_Width / 2;
	m_Center.y = m_Height / 2;
	Vector2f center{ m_Center.x, m_Center.y };
	m_DisplacementVector = center;
}