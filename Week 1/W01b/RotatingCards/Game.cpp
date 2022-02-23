#include "pch.h"
#include "Game.h"
#include "Texture.h"
#include "Card.h"
#include <iostream>
#include <vector>

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
	InitializeCards();
}

void Game::Cleanup( )
{
	DeleteCards();
}

void Game::Update( float elapsedSec )
{
	UpdateAngle(elapsedSec);

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

void Game::Draw( ) //const
{
	ClearBackground( );
	DrawCards();
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


void Game::InitializeCards()
{
	Circlef circle{ 250.f, 250.f, 50 };

	for (int suit{2}; suit < int(Card::Suit::hearts); suit++)
	{
		for (int rank{}; rank < int(Card::maxRank); rank++)
		{
			m_Cards.push_back(new Card(Card::Suit(suit + 1), rank + 1, 50.0f, circle));
		}
	}
}

void Game::DrawCards()
{
	for (size_t i{}; i < m_Cards.size(); ++i)
	{
		m_Cards.at(i)->Draw();
	}
}

void Game::UpdateAngle(float elapsed)
{
	for (size_t i{}; i < m_Cards.size(); ++i) {
		m_Cards.at(i)->Update(elapsed);
	}
}

void Game::DeleteCards() 
{
	for (size_t i{}; i < m_Cards.size(); ++i) {
		m_Cards.at(i)->~Card();
	}
}