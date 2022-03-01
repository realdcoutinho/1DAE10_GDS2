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
	DetermineHighestSmileys();
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawBorder();
	DrawSmileys();
}

void Game::ClearBackground() const
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_UP:
		IncreaseSmileysSpeed();
		break;
	case SDLK_DOWN:
		DecreaseSmileysSpeed();
		break;
	case SDLK_DELETE:
		//DeleteSleepers();
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

	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		for (int index{}; index < m_NrOfSmileys; ++index)
		{
			m_SmileysArray[index]->HitTest(mousePos);
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

Point2f Game::GetInitialPosition()
{
	float width{ float(std::rand() % int(m_Window.width)) - m_Border};

	Point2f initialPoint{ width, m_Window.height/2 };
	return initialPoint;
}

void Game::CreateSmileys()
{

	for (int index{}; index < m_NrOfSmileys; ++index)
	{
		Point2f position{ GetInitialPosition() };
		m_SmileysArray[index] = new Smiley(position);
	}
}

void Game::DrawSmileys() const
{
	for (int index{}; index < m_NrOfSmileys; ++index)
	{
		m_SmileysArray[index]->Draw();
	}
}

void Game::DeleteSmiley() 
{
	for (int index{}; index < m_NrOfSmileys; ++index)
	{
		m_SmileysArray[index]->~Smiley();
	}
}

void Game::UpdatePosition(float elapsed) 
{
	for (int index{}; index < m_NrOfSmileys; ++index)
	{
		m_SmileysArray[index]->Update(elapsed, m_BouncingRect, m_SafeRect);
	}
}

void Game::DrawBorder() const
{
	Color4f black{ 0,0, 0, 1 };
	SetColor(black);
	DrawRect(m_SafeRect);
}

void Game::IncreaseSmileysSpeed()
{
	for (int index{}; index < m_NrOfSmileys; ++index)
	{
		m_SmileysArray[index]->IncreaseSpeed();
	}
}

void Game::DecreaseSmileysSpeed()
{
	for (int index{}; index < m_NrOfSmileys; ++index)
	{
		m_SmileysArray[index]->DecreaseSpeed();
	}
}

void Game::DetermineHighestSmileys()
{
	float maxHeight{};
	for (int index{}; index < m_NrOfSmileys; ++index)
	{
		if (!(m_SmileysArray[index]->IsSleeping())) 
		{
			float height{ m_SmileysArray[index]->GetPosition().y };
			if (height > maxHeight)
			{
				maxHeight = height;
			}
		}
	}
	for (int index{}; index < m_NrOfSmileys; ++index)
	{
		if (m_SmileysArray[index]->GetPosition().y != maxHeight)
		{
			m_SmileysArray[index]->SetHighest(false);
		}
		else
		{
			m_SmileysArray[index]->SetHighest(true);
		}
	}
}

void Game::DeleteSleepers()
{
	for (int index{}; index < m_NrOfSmileys; ++index)
	{
		if (m_SmileysArray[index]->IsSleeping())
		{
			delete m_SmileysArray[index];
			m_SmileysArray[index] = nullptr;
		}
	}
}