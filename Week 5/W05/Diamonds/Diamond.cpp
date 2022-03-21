#include "pch.h"
#include "Diamond.h"
#include <iostream>
using namespace utils;

Diamond::Diamond(Point2f center)
	: m_centerPoint{ center }
	, m_InitialCenterPoint{center}
{
	InitializeVertices();
	InitializeTexture();
	CalculateSpeed();
	std::cout << "A new Diamond was created" << '\n';
}

Diamond::~Diamond()
{
	DeleteTextures();
	std::cout << "Diamond and Points Deleted" << '\n';
}

void Diamond::DrawDiamondPoints() const
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
	DrawPolygon(inWorldVertices, true, 7.0f);

}

void Diamond::DrawDiamondTexture() const
{
	Point2f center{ m_centerPoint.x - m_Lenght / 2, m_centerPoint.y - m_Lenght / 2 };
	glPushMatrix();
	glTranslatef(m_DisplacementVector.x, m_DisplacementVector.y, 0);
	glTranslatef(m_centerPoint.x, m_centerPoint.y, 0);
	glRotatef(m_RotationAngle, 0, 0, 1);
	glScalef(m_Scale, m_Scale, 0);
	glTranslatef(- m_Lenght / 2, -m_Lenght / 2, 0);
	m_pTextureDiamond->Draw();
	glPopMatrix();
}

void Diamond::RotateDiamond(float elapsedSec)
{

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_A])
	{
		m_RotationDiretion = 1;
	}
	if (pStates[SDL_SCANCODE_D])
	{
		m_RotationDiretion = -1;
	}
	m_RotationAngle += m_RotationSpeed * elapsedSec * m_RotationDiretion;
}

void Diamond::ScaleDiamond(float elapsedSec)
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

void Diamond::TranslateDiamond(float elapsedSec) 
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

void Diamond::IsPointInDiamond(Point2f mousePos)
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

void Diamond::CalculateSpeed()
{
	int speed{ rand() % 130 - 50 };
	m_RotationSpeed = float(speed);
}

void Diamond::Matrices(float elapsedSec)
{
	switch (m_State)
	{
	case(State::deselected):
		RotateDiamond(elapsedSec);
		ScaleDiamond(elapsedSec);
		TranslateDiamond(elapsedSec);

		break;
	case(State::selected):
		break;
	}
	Matrix2x3 matTranslateToOrigin, matRotate, matScale, matTranslateToWorldSpace, matTranslateToStart;
	Vector2f center{ m_centerPoint };

	matTranslateToOrigin.SetAsTranslate(-center); // move it to origin
	matRotate.SetAsRotate(m_RotationAngle);
	matScale.SetAsScale(m_Scale);
	matTranslateToStart.SetAsTranslate(center); // move to starting position
	matTranslateToWorldSpace.SetAsTranslate(m_DisplacementVector); // move it back to its world space
	m_matWorld = matTranslateToWorldSpace * matTranslateToStart * matRotate * matScale * matTranslateToOrigin;
}

void Diamond::InitializeVertices()
{
	Point2f p1{ m_centerPoint.x - m_Lenght/2,  m_centerPoint.y };
	Point2f p2{ m_centerPoint.x,  m_centerPoint.y  - m_Lenght/2};
	Point2f p3{ m_centerPoint.x + m_Lenght/2,  m_centerPoint.y };
	Point2f p4{ m_centerPoint.x ,  m_centerPoint.y + m_Lenght/2};

	m_Vertices.push_back(p1);
	m_Vertices.push_back(p2);
	m_Vertices.push_back(p3);
	m_Vertices.push_back(p4);
}

void Diamond::InitializeTexture()
{
	std::string filename{ "images/Diamond.png" };
	m_pTextureDiamond = new Texture(filename);
}

void Diamond::PressR()
{
	m_State = State::deselected;
	m_Scale = 1;
	//Matrix2x3 matTranslateToStart;
	//Vector2f center{ m_centerPoint };
	//matTranslateToStart.SetAsTranslate(center);
	//m_matWorld = matTranslateToStart;
	m_RotationDiretion = 0;
}

void Diamond::DeleteTextures()
{
	delete m_pTextureDiamond;
	m_pTextureDiamond = nullptr;
	std::cout << "Texture Deleted" << '\n';
}