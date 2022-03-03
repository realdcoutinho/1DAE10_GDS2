#include "pch.h"
#include "Game.h"
#include "Enemy.h"
#include "Avatar.h"
#include "utils.h"
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
	InitializeEnemy();
	InitializeAvatar();
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{

	m_pAvatar->Update(elapsedSec, m_pEnemy, m_NrOfEnemies);





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
	DrawEnemy();
	DrawAvatar();
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
	Point2f mousePos{ (float)e.x, (float)e.y };

	std::cout << "MOUSEBUTTONDOWN event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		std::cout << " left button " << std::endl;
		for (int index{}; index < m_NrOfEnemies; ++index)
		{
			m_pEnemy[index]->DoHitTest(mousePos);
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
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::InitializeEnemy()
{
	float rows{ 4 };
	float columns{ 10 };
	float enemySize{ 30 };
	float border{ 10 };

	Point2f center{ border + enemySize / 2, m_Window.height - border - enemySize / 2 };

	for (int index{}; index < m_NrOfEnemies; ++index)
	{
		if ((index +1) % 10 == 0)
		{
			m_pEnemy[index] = new Enemy(center, enemySize, enemySize);
			std::cout << "hey" << '\n';
			center.y -= enemySize + border;
			center.x = border + enemySize / 2;
		}
		else
		{
			m_pEnemy[index] = new Enemy(center, enemySize, enemySize);
			center.x += enemySize + border;
		}
	}
}

void Game::DrawEnemy() const
{
	for (int index{}; index < m_NrOfEnemies; ++index)
	{
		m_pEnemy[index]->Draw();
	}
}

void Game::InitializeAvatar()
{
	float avatarSize{ 40 };

	Point2f center{ m_Window.width / 2,avatarSize / 2};
	m_pAvatar = new Avatar(center, avatarSize, avatarSize);
}

void Game::DrawAvatar() const
{
	m_pAvatar->Draw();
}