#pragma once
#include "SoundEffect.h"
#include "SoundStream.h"
#include "Texture.h"


class Game final
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update(float elapsedSec);
	void Draw() const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;

	//Which test series
	bool m_StreamTest;
	const Texture m_StreamMenuText;
	const Texture m_EffectMenuText;

	const std::string path1{ "Resources/Sounds/Donkeykong.mp3" };
	SoundStream* m_pSoundStreamDonkey;
	SoundStream* m_pSoundStreamMario;
	
	SoundEffect* m_pSoundEffectLase;
	SoundEffect* m_pSoundEffectJingles;



	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void DrawMenu( ) const;
	void SwitchTest( );
	void TestStreams( const SDL_KeyboardEvent& e );
	void TestEffects( const SDL_KeyboardEvent& e );

};