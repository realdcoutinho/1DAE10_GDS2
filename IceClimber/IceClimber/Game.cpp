#include "pch.h"
#include "Game.h"
#include "Camera.h"
#include "Level.h"
#include "Player.h"
#include <iostream>

Game::Game( const Window& window ) 
	:m_Window{ window }
	, m_pLevel{ new Level{window.width, window.height} }
	, m_pPlayer{ new Player{Point2f{256 / 2, 24}, Point2f{256 / 2, 24} } }
{
	SetScale();
	InitializeCamera(window);
	Initialize();
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
	delete m_pLevel;
	delete m_pCamera;
	delete m_pPlayer;
}

void Game::Update( float elapsedSec )
{
	m_pLevel->GetPlayerState(m_pPlayer->GetPlayerState());
	m_pPlayer->Update(elapsedSec, m_pLevel);
	std::cout << "Hello";
	m_pLevel->Update(elapsedSec);
	m_pLevel->GetActorShape(m_pPlayer->GetShape());

	m_pCamera->Update(elapsedSec);
	m_pPlayer->SetWinning(m_pLevel->IsWinning());
	//std::cout << time << '\n';
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
	DrawBackground();

	ClearBackground();
	glPushMatrix();
	{	
		glScalef(m_Scale, m_Scale, 1);
		m_pCamera->Transform(m_pPlayer->GetShape(), m_pPlayer->GetIsOnGround());
		DrawBackground();
		m_pPlayer->Draw();
	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;

	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_UP:
	//	m_pCamera->TransformUp();
	//	break;
	//case SDLK_DOWN:
	//	m_pCamera->TransformDown();
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}



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
	std::cout << "MOUSEBUTTONDOWN event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		std::cout << " left button " << std::endl;
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


void Game::DrawBackground() const
{
	m_pLevel->Draw();
} 

void Game::SetScale()
{
	m_Scale = m_pLevel->GetScale();
}

void Game::InitializeCamera(const Window& window)
{
	m_pCamera = new Camera{ window.width / m_Scale, window.height / m_Scale };
	m_pCamera->SetLevelBounderies(m_pLevel->GetBoundaries());
}
