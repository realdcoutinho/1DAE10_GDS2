#include "pch.h"
#include "Game.h"
#include "Camera.h"
#include "Level.h"
#include "Player.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "HUD.h"
#include <iostream>
#include "utils.h"
using namespace utils;

Game::Game( const Window& window ) 
	:m_Window{ window }
	, m_Offset{ 100.0f }
	, m_pTextures{ new TextureManager()}
	, m_pSoundManager{new SoundManager()}
	, m_pPlayer{ new Player{this, Point2f{256 / 2 + m_Offset, 24}, Point2f{256 / 2 + m_Offset, 24} } }
	, m_pLevel{ new Level{this, m_pPlayer, window.width, window.height} }
	, m_Pause{false}
	, m_GameEnd{ false }
{
	SetScale();
	InitializeCamera(window);
	Initialize();
	PrintControls();
	PrintMessage();

	const float hudOffset{ 50.0f };
	Point2f BL{50, window.height - hudOffset };
	m_pHUD = new HUD{m_pTextures, m_pPlayer, BL, 3};
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pSoundManager->GetSoundStreamPointer("GameMusic")->Play(1);
}

void Game::Cleanup( )
{
	delete m_pTextures;
	delete m_pLevel;
	delete m_pCamera;
	delete m_pPlayer;
	delete m_pHUD;
	delete m_pSoundManager;
}

void Game::Update( float elapsedSec )
{

	if (!m_Pause && !(m_pPlayer->GetIsWinning()))
	{
		m_pLevel->GetPlayerState(m_pPlayer->GetPlayerState());
		m_pPlayer->Update(elapsedSec, m_pLevel);
		m_pLevel->Update(elapsedSec);
		m_pLevel->SetActorShape(m_pPlayer->GetShape());
		m_pPlayer->SetWinning(m_pLevel->IsWinning());
		m_pHUD->LostLife();
		m_pSoundManager->GetSoundStreamPointer("GameMusic")->Resume();
		m_pSoundManager->UpdateStates();
	}
	else
	{
		m_pSoundManager->GetSoundStreamPointer("GameMusic")->Pause();
	}
	if (m_pPlayer->GetIsWinning())
		if (!m_GameEnd)
		{
			m_pSoundManager->GetSoundEffectPointer("Winning")->Play(0);
			m_GameEnd = true;
		}
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
	m_pHUD->Draw();
	Rectf rect{ 0, 0, 50, 100 };
	//FillRect(rect);
	if (m_Pause)
	{
		SetColor(Color4f(0, 0, 0, 0.5));
		FillRect(Point2f{ 0, 0 }, m_Window.width, m_Window.height);
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;

	switch ( e.keysym.sym )
	{
	case SDLK_t:
		//std::cout << "Left arrow key released\n";
		m_pSoundManager->DescreaseVolume(-1);
		break;
	case SDLK_y:
		//std::cout << "`Right arrow key released\n";
		m_pSoundManager->IncreaseVolume(1);
		break;
	case SDLK_u:
		//std::cout << "`Right arrow key released\n";
		m_pSoundManager->PrintVolume();
		break;
	}



}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_l:
		PrintControls();
		break;
	case SDLK_p:
		Pause();
		break;
	case SDLK_m:
		m_pSoundManager->ChangeMusic();
		break;
	case SDLK_n:
		m_pSoundManager->ChangeAllSounds();
		break;
	case SDLK_i:
		PrintMessage();
		break;
	}
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
	m_pCamera = new Camera{ m_pPlayer, window.width / m_Scale, window.height / m_Scale };
	Rectf cameraPosition{ m_pLevel->GetBoundaries().left + m_Offset, m_pLevel->GetBoundaries().bottom, m_pLevel->GetBoundaries().width, m_pLevel->GetBoundaries().height};
	m_pCamera->SetLevelBounderies(m_pLevel->GetBoundaries());
}

TextureManager* Game::GetTextureManager()
{
	return m_pTextures;
}

SoundManager* Game::GetSoundManagerPointer()
{
	return m_pSoundManager;
}

void Game::PrintControls()
{
	std::cout << "Controls:" << '\n';
	std::cout << "Press P to pause the game" << '\n';
	std::cout << "Press T to increase volume" << '\n';
	std::cout << "Press Y to decrease volume" << '\n';
	std::cout << "Press M to turn off music" << '\n';
	std::cout << "Press N to turn Off sound effects" << '\n';
	std::cout << "Press N to turn Off sound effects" << '\n';
	std::cout << "Press X to jump" << '\n';
	std::cout << "Press Z to to kill" << '\n';
	std::cout << "Press U for sound information" << '\n';
	std::cout << "Press I for game instructions" << '\n';
	std::cout << "Use either WASD or arrows to move" << '\n';
	std::cout << '\n';

}

void  Game::PrintMessage()
{
	std::cout << "Message:" << '\n';
	std::cout << "Welcome Climber!" << '\n';
	std::cout << "Today we have a dangerous hike ahead of us." << '\n';
	std::cout << "Your goal? Reach the top of the mountain without" << '\n';
	std::cout << "getting hit by a stalagmite, a stalagtite of caught" << '\n';
	std::cout << "by the mountain guards!" << '\n';
	std::cout << "You can use your spike to destroy the blocks, which" << '\n';
	std::cout << "will open you a path foward. They also to destroy the" << '\n';
	std::cout << "stalagmites, stalgtites and the guards. The stalagtites" << '\n';
	std::cout << "cause no harm while forming but they are extremly dangerous" << '\n';
	std::cout << "if they hit you during their fall." << '\n';
	std::cout << "The journey ahead will be challenging! Pick all the food items" << '\n';
	std::cout << "along the way. It will make your score higher!" << '\n';
	std::cout << "At the very top will be a friendly bird. Your objective is to catch" << '\n';
	std::cout << "him so he can take you to the base of the next mountain." << '\n';
	std::cout << "Good Luck! Dont get killed...." << '\n';

	std::cout << '\n';
}



void Game::Pause()
{
	if (!m_Pause)
		m_Pause = true;
	else
		m_Pause = false;
}