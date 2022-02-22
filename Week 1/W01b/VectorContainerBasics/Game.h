#pragma once

class Card;
#include <vector>

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
	void Draw();// const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;

	std::vector<int> m_vector;
	std::vector<Card*> m_Cards;


	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void PlusPressed();
	void MinusPressed();
	void UpPressed();
	void DownPressed();

	void InitializeCards();
	void DrawCards();
	void DeleteCards();
	void ShuffleCards();

	int GetIndex(int rowIndex, int columnIndex, int nrOfColumns);
};