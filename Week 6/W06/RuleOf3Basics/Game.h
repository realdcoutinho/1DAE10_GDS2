#pragma once
#include "Container.h"
#include "Texture.h"

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

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	//my data members
	static Texture m_StatDaeTexture;
	Texture m_DaeTexture;

	//my functions
	void AddValues(Container &c, int nr, int min, int max);
	void TestContainer();
	void PrintContainer(Container& c);

	Container CreateMultiple(Container c, int factor);
	void DrawTexture(Texture texture, const Point2f& pos, int nr, int dx, int dy) const;
};