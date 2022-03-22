#include "pch.h"
#include "Game.h"
#include "Diamond.h"

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
	InitializeDiamonds();
}

void Game::Cleanup( )
{
	for (Diamond* diamond : pDiamonds)
	{
		diamond->~Diamond();
	}
}

void Game::Update( float elapsedSec )
{
	for (Diamond* diamond : pDiamonds)
	{
		diamond->Matrices(elapsedSec);
	}






	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDL_SCANCODE_R] )
	{
		for (Diamond* diamond : pDiamonds)
		{
			diamond->PressR();
		}
	}

}

void Game::Draw( ) const
{
	ClearBackground( );
	for (Diamond* diamond : pDiamonds)
	{
		diamond->DrawDiamondPoints();
	}
	for (Diamond* diamond : pDiamonds)
	{
		diamond->DrawDiamondTexture();
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{

}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	Point2f mouseposition{ (float)e.x, (float)e.y };
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		for (Diamond* diamond : pDiamonds)
		{
			diamond->IsPointInDiamond(mouseposition);
		}
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
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}


void Game::InitializeDiamonds()
{
	Point2f centerOne{ 100, 100 };
	Point2f centerTwo{ 150, 200 };
	Point2f centerThree{ 500, 70 };
	Point2f centerFour{ 400, 400 };
	Point2f centerFive{ 700, 300 };
	Diamond* diamondOne{ new Diamond(centerOne)};
	Diamond* diamondTwo{ new Diamond(centerTwo) };
	Diamond* diamondThree{ new Diamond(centerThree) };
	Diamond* diamondFour{ new Diamond(centerFour) };
	Diamond* diamondFive{ new Diamond(centerFive) };
	pDiamonds.push_back(diamondOne);
	pDiamonds.push_back(diamondTwo);
	pDiamonds.push_back(diamondThree);
	pDiamonds.push_back(diamondFour);
	pDiamonds.push_back(diamondFive);
}