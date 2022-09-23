#pragma once


class Camera;
class Level;
class Player;
class TextureManager;
class HUD;
class SoundManager;
#include "TextureManager.h"

class Game final
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	TextureManager* GetTextureManager();
	SoundManager* GetSoundManagerPointer();


	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
	void SetScale();
	void DrawBackground() const;
	void InitializeCamera(const Window& window);

	void PrintControls();
	void PrintMessage();
	void Pause();

	
	bool m_Pause;
	bool m_GameEnd;

	float m_Offset;
	float m_Scale;
	float time{};

	const Window m_Window;
	SoundManager* m_pSoundManager;
	TextureManager* m_pTextures;
	Camera* m_pCamera;
	Player* m_pPlayer;
	Level* m_pLevel;
	HUD* m_pHUD;

};