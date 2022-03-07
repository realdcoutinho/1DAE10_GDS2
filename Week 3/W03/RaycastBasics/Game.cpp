#include "pch.h"
#include "Game.h"
#include <iostream>
using namespace utils;


Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	InitializeVertices();
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawSurface();
	DrawRaycast();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;

	Point2f pos{ float(e.x), float(e.y) };
	m_MousePos = pos;
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
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}


void Game::InitializeVertices()
{
	m_Vertices.push_back(Point2f{ m_Window.width * 0.5f, m_Window.height * 0.1f });
	m_Vertices.push_back(Point2f{ m_Window.width * 0.9f , m_Window.height * 0.2f });
	m_Vertices.push_back(Point2f{ m_Window.width * 0.9f, m_Window.height * 0.7f });
	m_Vertices.push_back(Point2f{ m_Window.width * 0.5f, m_Window.height * 0.9f });
	m_Vertices.push_back(Point2f{ m_Window.width * 0.1f, m_Window.height * 0.7f });
	m_Vertices.push_back(Point2f{ m_Window.width * 0.1f, m_Window.height * 0.2f });
}



void Game::DrawSurface() const
{
	SetColor(Color4f{ 0.0f, 0.0f, 0.0f, 1.0f }); //black
	FillPolygon(m_Vertices);
	SetColor(Color4f{ 1.0f, 0.5f, 0.2f, 1.0f }); //orange
	DrawPolygon(m_Vertices);
}

void Game::DrawRaycast() const
{
	Point2f rayP1{ m_Window.width / 2, m_Window.height / 2 };
	Point2f rayP2{ 50, 500 };

	rayP2 = m_MousePos;
	//Do the rayCast
	HitInfo hitInfo{};

	if (Raycast(m_Vertices, rayP1, rayP2, hitInfo))
	{
		//hit point in purple
		Point2f intersection{ hitInfo.intersectPoint.x, hitInfo.intersectPoint.y };
		Vector2f rayP2Vector{ rayP2 };
		SetColor(Color4f{ 1.0f, 0.0f, 1.0f, 1.0f });
		DrawLine(rayP1, intersection, 2);
		DrawEllipse(hitInfo.intersectPoint, 4, 4);
		SetColor(Color4f{ 1.0f, 0.0f, 0.0f, 1.0f });
		DrawLine(intersection, rayP2, 2);


		//normal vector of the hit surface
		SetColor(Color4f{ 0.0f, 1.0f, 0.0f, 1.0f });
		//Vector2f normal{ }
		DrawVector((hitInfo.normal * 30)*-1, hitInfo.intersectPoint);
		DrawVector((hitInfo.normal * 30), hitInfo.intersectPoint);

		//reflected ray(white)
		//vector2f has a reflected method, parameter is the normal on the surface
		SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
		Vector2f rayVector{ rayP1, rayP2 };
		Vector2f reflectedRay{ rayVector.Reflect(hitInfo.normal) };
		SetColor(Color4f{ 1.0f, 0.5f, 1.0f, 1.0f });
		DrawVector(reflectedRay, hitInfo.intersectPoint);
		SetColor(Color4f{ 0.5f, 0.0f, 1.0f, 1.0f });
		DrawVector(reflectedRay * (1 - hitInfo.lambda), hitInfo.intersectPoint);

	}
	else
	{
		SetColor(Color4f{ 1.0f, 1.0f, 0.0f, 1.0f });
		DrawLine(rayP1, rayP2, 2);
	}
}