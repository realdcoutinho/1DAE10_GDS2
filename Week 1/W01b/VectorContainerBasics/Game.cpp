#include "pch.h"
#include "Game.h"
#include "Texture.h"
#include <iostream>

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
	DeleteCards();
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



}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;

	//std::cout << "KEYDown event: " << e.keysym.sym << std::endl;
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		PlusPressed();
		//std::cout << "Plus arrow key pressed\n";
		break;
	case SDLK_DOWN:
		MinusPressed();
		//std::cout << "Minus arrow key pressed\n";
		break;
	case SDLK_RIGHT:
		Game::UpPressed();
		break;
	case SDLK_LEFT:
		Game::DownPressed();
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

void Game::PlusPressed()
{
	int value{ rand() % 31 };
	m_vector.push_back(value);

	//for (int i{}; i < m_vector.size(); ++i)
	//{
	//	std::cout << m_vector[i] << " ";
	//}

	for (int i : m_vector)
	{
		std::cout << i << " ";
	}

	std::cout << '\n';
}

void Game::MinusPressed()
{
	if (m_vector.size() != 0) {
		m_vector.pop_back();
	}
	else {
		return;
	}

	//for (int i{}; i < m_vector.size(); ++i)
	//{
	//	std::cout << m_vector[i] << " ";
	//}

	for (int i : m_vector)
	{
		std::cout << i << " ";
	}
	std::cout << '\n';
}

void Game::UpPressed(){

	for (int i{}; i < m_vector.size(); ++i)
	{
		m_vector[i] = m_vector[i] + 1;
		std::cout << m_vector[i] << " ";
	}

	//for (int i : m_vector)
	//{
	//	m_vector[i] = m_vector[i] + 1;
	//	std::cout << i << " ";
	//}

	std::cout << '\n';
}

void Game::DownPressed() {

	for (int i{}; i < m_vector.size(); ++i)
	{
		m_vector[i] = m_vector[i] - 1;
		std::cout << m_vector[i] << " ";
	}

	//for (int i : m_vector)
	//{
	//	m_vector[i] = m_vector[i] + 1;
	//	std::cout << i << " ";
	//}

	std::cout << '\n';
}

void Game::InitializeCards() 
{
	for (int suite = 0; suite < 4; suite++)
	{
		for (int card{ 0 }; card < 13; card++)
		{
			
		}
	}
}

void Game::DeleteCards() 
{
	for (int i{}; i < m_NumberOfCards; ++i)
	{
		delete m_pCards[i];
	}
}