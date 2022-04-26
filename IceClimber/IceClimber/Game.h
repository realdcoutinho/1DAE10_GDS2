#pragma once


class Camera;
class Level;
class Player;
class TextureManager;
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


	


	float m_Scale;
	float time{};

	const Window m_Window;
	TextureManager* m_pTextures;
	Camera* m_pCamera;
	Player* m_pPlayer;
	Level* m_pLevel;
};