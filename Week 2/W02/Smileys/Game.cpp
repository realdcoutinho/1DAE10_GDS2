#include "pch.h"
#include "Game.h"
#include "Smiley.h"
#include "utils.h"
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
	CreateSmileys();
}

void Game::Cleanup( )
{
	DeleteSmiley();
}

void Game::Update( float elapsedSec )
{
	UpdatePosition(elapsedSec);

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
	DrawBorder();
	DrawSmileys();


	Point2f ground{ 800, 0 };
	Point2f top{ 800, 500 };
	//DrawLine(ground, top);
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;

	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_LEFT:
		std::cout << "Left arrow key released\n";
		IncreaseSpeed();
		break;
	case SDLK_RIGHT:
		std::cout << "`Right arrow key released\n";
		DecreaseSpeed();
		break;
	case SDLK_1:
	case SDLK_KP_1:
		std::cout << "Key 1 released\n";
		break;
	}

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
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{


	Point2f mousePos{ float(e.x), float(e.y) };


	std::cout << "MOUSEBUTTONDOWN event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		std::cout << " left button " << std::endl;
		for (int i{}; i < m_NrOfSmileys; ++i)
		{
			m_SmileysArray[i]->HitTest(mousePos);
		}
		break;
	case SDL_BUTTON_RIGHT:
		std::cout << " right button " << std::endl;
		break;
	case SDL_BUTTON_MIDDLE:
		std::cout << " middle button " << std::endl;
		break;
	}
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
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}


Point2f Game::GetInitialPosition()
{
	float width{ float(std::rand() % 900) - 50};

	Point2f initialPoint{ width, 250.0f };
	return initialPoint;
}

void Game::CreateSmileys()
{

	for (int i{}; i < m_NrOfSmileys; ++i)
	{
		Point2f position{ GetInitialPosition() };
		m_SmileysArray[i] = new Smiley(position);
	}
}

void Game::DrawSmileys() const
{
	for (int i{}; i < m_NrOfSmileys; ++i)
	{
		m_SmileysArray[i]->Draw();
	}
}

void Game::DeleteSmiley() 
{
	for (int i{}; i < m_NrOfSmileys; ++i)
	{
		m_SmileysArray[i]->~Smiley();
	}
}

void Game::UpdatePosition(float elapsed) 
{
	for (int i{}; i < m_NrOfSmileys; ++i)
	{
		m_SmileysArray[i]->Update(elapsed, m_BouncingRect, m_SafeRect);
	}
}

void Game::DrawBorder() const
{
	Color4f black{ 0,0, 0, 1 };
	SetColor(black);
	DrawRect(m_Border, m_Border, 900 - m_Border*2, 500 - m_Border*2);
}

void Game::IncreaseSpeed()
{
	for (int i{}; i < m_NrOfSmileys; ++i)
	{
		m_SmileysArray[i]->IncreaseSpeed();
	}
}

void Game::DecreaseSpeed()
{
	for (int i{}; i < m_NrOfSmileys; ++i)
	{
		m_SmileysArray[i]->DecreaseSpeed();
	}
}