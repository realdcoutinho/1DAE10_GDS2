#include "pch.h"
#include "Game.h"
#include "TrafficLight.h"
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
	InitializeTrafficLights();
}

void Game::Cleanup( )
{
	DeleteTrafficLights();
}

void Game::Update( float elapsedSec )
{
	UpdateLights(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawTrafficLights();
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
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	Point2f mouPos{ (float)e.x, (float)e.y };
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		for (size_t i{}; i < m_Lights.size(); ++i)
		{
			m_Lights.at(i)->DoHitTest(mouPos);
		}
		break;
	}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::InitializeTrafficLights()
{
	float width{ 90 };
	float height{ 240 };
	float border{ 7 };


	for (int rows{}; rows < 2; ++rows)
	{
		for (int columns{}; columns < 5; ++columns)
		{
			Point2f pos{ border + width * columns + border * columns, border + height * rows + border * rows};
			m_Lights.push_back(new TrafficLight(pos, width, height));
		}
	}
}

void Game::DrawTrafficLights() const
{
	for (size_t i{}; i < m_Lights.size(); ++i)
	{
		m_Lights.at(i)->Draw();
	}
}

void Game::UpdateLights(float elapsed)
{
	for (size_t i{}; i < m_Lights.size(); ++i)
	{
		m_Lights.at(i)->Update(elapsed);
		m_Lights.at(i)->LightChange();
	}
}

void Game::DeleteTrafficLights()
{
	for (size_t i{}; i < m_Lights.size(); ++i)
	{
		delete m_Lights.at(i);
		m_Lights.at(i) = nullptr;
	}
}