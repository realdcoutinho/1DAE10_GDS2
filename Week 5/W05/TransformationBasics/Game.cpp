#include "pch.h"
#include "Game.h"
#include <iostream>
//#include "Matrix2x3.h"
using namespace utils;

Game::Game(const Window& window)
	:m_Window{ window }
{
	Initialize();

}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	InitializeVertices();
	InitializeTexture();
	CalculateSpeed();
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	RotateDiamond(elapsedSec);
	ScaleDiamond(elapsedSec);
	TranslateDiamond(elapsedSec);
	Matrices();
}

void Game::Draw() const
{
	ClearBackground();

	DrawDiamondPoints();
	DrawDiamondTexture();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		break;
	case SDLK_RIGHT:
		//std::cout << "`Right arrow key released\n";
		break;
	case SDLK_1:
		break;
	case SDLK_KP_1:
		//std::cout << "Key 1 released\n";
		break;
	case SDLK_a:
		m_RotationDiretion = 1;
		break;
	case SDLK_d:
		m_RotationDiretion = -1;
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	Point2f mouseposition{ (float)e.x, (float)e.y };
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		IsPointInDiamond(mouseposition);
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

void Game::InitializeVertices()
{
	Point2f p1{ 0, m_Height/2 };
	Point2f p2{ m_Width/2, 0 };
	Point2f p3{ m_Width, m_Height/2 };
	Point2f p4{ m_Width/2, m_Height };

	m_Vertices.push_back(p1);
	m_Vertices.push_back(p2);
	m_Vertices.push_back(p3);
	m_Vertices.push_back(p4);
}

void Game::InitializeTexture()
{
	std::string filename{ "images/Diamond.png"};
	m_pTextureDiamond = new Texture(filename);
}

void Game::DrawDiamondPoints() const
{
	std::vector<Point2f> inWorldVertices{ m_matWorld.Transform(m_Vertices) };

	switch (m_State)
	{
	case(State::deselected):
		SetColor(Color4f(0.0f, 0.0f, 1.0f, 1.0f));
		break;
	case(State::selected):
		SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	}
	DrawPolygon(inWorldVertices, true, 2.5f);
}

void Game::DrawDiamondTexture() const
{
	glPushMatrix();
	glTranslatef(m_DisplacementVector.x, m_DisplacementVector.y, 0);
	glTranslatef(m_centerPoint.x, m_centerPoint.y, 0);
	glRotatef(m_RotationAngle, 0, 0, 1);
	glScalef(m_Scale, m_Scale, 0);
	glTranslatef(-m_centerPoint.x, -m_centerPoint.y, 0);
	m_pTextureDiamond->Draw();
	glPopMatrix();
}

void Game::RotateDiamond(float elapsedSec)
{
	m_RotationAngle += m_RotationSpeed * elapsedSec * m_RotationDiretion;
}

void Game::ScaleDiamond(float elapsedSec)
{
	//Check keyboard state
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_W])
	{
		m_Scale *= 1 + 3 * elapsedSec;
		std::cout << "big" << '\n';
	}
	if (pStates[SDL_SCANCODE_S])
	{
		m_Scale /= 1 + 3 * elapsedSec;
		std::cout << "small" << '\n';
	}
}

void Game::TranslateDiamond(float elapsedSec)
{
	int directionX{ 0 };
	int directionY{ 0 };
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_UP])
	{
		directionY = 1;
	}
	if (pStates[SDL_SCANCODE_DOWN])
	{
		directionY = -1;
	}
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		directionX = 1;
	}
	if (pStates[SDL_SCANCODE_LEFT])
	{
		directionX = -1;
	}
	m_DisplacementVector.x += directionX * 120 * elapsedSec;
	m_DisplacementVector.y += directionY * 120 * elapsedSec;
}

void Game::CalculateSpeed()
{
	int speed{ rand() % 130 - 50};
	m_RotationSpeed = float(speed);
}

void Game::Matrices()
{
	m_centerPoint = GetMiddle(m_Vertices[0], m_Vertices[2]);
	Vector2f center{ m_centerPoint };

	Matrix2x3 matTranslateToOrigin, matRotate, matScale, matTranslateToWorldSpace, matTranslateToStart;

	matTranslateToOrigin.SetAsTranslate(-center); // move it to origin
	matRotate.SetAsRotate(m_RotationAngle);
	matScale.SetAsScale(m_Scale);
	matTranslateToStart.SetAsTranslate(center); // move to starting position
	matTranslateToWorldSpace.SetAsTranslate(m_DisplacementVector); // move it back to its world space

	m_matWorld = matTranslateToWorldSpace * matTranslateToStart * matRotate * matScale  * matTranslateToOrigin;
}

void Game::IsPointInDiamond(Point2f mousePos)
{
	std::vector<Point2f> polygon{ m_matWorld.Transform(m_Vertices) };
	
	if (IsPointInPolygon(mousePos, polygon) && (m_State == State::selected))
	{
		m_State = State::deselected;
	}
	else if (IsPointInPolygon(mousePos, polygon) && (m_State == State::deselected))
	{
		m_State = State::selected;
	}
}