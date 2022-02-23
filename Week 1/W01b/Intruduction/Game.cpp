#include "pch.h"
#include "Game.h"
#include "Ball.h"
#include "Texture.h"
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
	for (int i{}; i < m_NumberOfBalls; ++i)
	{
		float radius{ 50 };
		m_BallPtrs[i] = new Ball{
		Point2f{rand() % (int)(m_Window.width - 2 * radius) + radius, rand() % (int)(m_Window.height - 2 * radius) + radius},
		Vector2f{100, 100},
		Color4f{1, 0, 0, 1},
		radius
		};
	}

	m_pTexture = new Texture{"resources/dae.png"};
	VectorTest();
}

void Game::Cleanup( )
{
	for (int i{}; i < m_NumberOfBalls; ++i)
	{
		delete m_BallPtrs[i];

	}

	delete m_pTexture;

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

	for (int i{}; i < m_NumberOfBalls; ++i)
	{
		m_BallPtrs[i]->Update(elapsedSec, Rectf{ 0, 0, m_Window.width, m_Window.height });
	}

	m_Angle += elapsedSec * 120;

}

void Game::Draw( ) const
{
	ClearBackground( );

	for (int i{}; i < m_NumberOfBalls; ++i)
	{
		m_BallPtrs[i]->Draw();
	}

	glPushMatrix();
	glTranslatef(100, 0, 0);
	glRotatef(m_Angle, 0, 0, 1);
	glTranslatef(100, 0, 0);
	glScalef(1.5f, 1.5f, 1.0f);
	m_pTexture->Draw(Point2f{-m_pTexture->GetWidth() / 2, -m_pTexture->GetHeight() / 2});
	glPopMatrix();
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


void Game::VectorTest()
{
	std::vector<int> numbers{ 2, 4, 6, 8, 10, 12 };
	numbers.push_back(14);

	for (int i{}; i < numbers.size(); ++i) 
	{
		std::cout << i << '\t' << numbers[i] << '\n';
	}
	std::cout << '\n';
	numbers.pop_back();

	for (int value : numbers)
	{
		std::cout << value << ' ';
	}

	//Not the same as above
	//for (int value{}; value < numbers.size(); ++value)
	//{
	//	std::cout << value << ' ';
	//}

	std::cout << '\n';

}
