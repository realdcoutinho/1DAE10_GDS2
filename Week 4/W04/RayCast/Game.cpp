#include "pch.h"
#include "Game.h"
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
	Demo();
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

void Game::Demo() const
{
	//The surface (orange)
	Point2f surfP1{ 350.0f, 50.0f };
	Point2f surfP2{ 150.0f, 250.0f };
	SetColor(Color4f{ 1.0f, 0.5f, 0.2f, 1.0f });
	DrawLine(surfP1, surfP2, 2);

	//The Ray (yellow)
	Point2f p1{ 100, 40 };
	Point2f p2{ 380, 180 };

	SetColor(Color4f{ 1.0f, 1.0f, 0.0f, 1.0f });
	
	
	
	p2 = m_MousePos;
	//Do the rayCast
	HitInfo hitInfo{};
	std::vector<Point2f> surface{ surfP1, surfP2 };
	if (Raycast(surface, p1, p2, hitInfo))
	{

		Point2f intersection{ hitInfo.intersectPoint.x, hitInfo.intersectPoint.y };
		DrawLine(p1, intersection, 2);
		//Hitpoint(yellow)
		SetColor(Color4f{ 1.0f, 1.0f, 0.0f, 1.0f });
		DrawEllipse(hitInfo.intersectPoint, 4, 4);

		//normal (green)
		SetColor(Color4f{ 0.0f, 1.0f, 0.0f, 1.0f });
		DrawVector(hitInfo.normal * 100, hitInfo.intersectPoint);


		//reflected ray(white)
		//vector2f has a reflected method, parameter is the normal on the surface
		SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
		Vector2f rayVector{ p1, p2 };
		Vector2f reflectedRay{ rayVector.Reflect(hitInfo.normal) };

		//DrawVector(reflectedRay, hitInfo.intersectPoint);
		DrawVector(reflectedRay * (1 - hitInfo.lambda), hitInfo.intersectPoint);
	}
	else {
		DrawLine(p1, p2, 2);
	}
}

