#pragma once
class Smiley;

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

	//mine
	static const int m_NrOfSmileys{ 10 };
	Smiley* m_SmileysArray[m_NrOfSmileys];
	float m_Border{ 30};
	Rectf m_SafeRect{ m_Border, m_Border, 900 - m_Border * 2, 500 - m_Border * 2 };
	Rectf m_BouncingRect{ 0, 0, 900, 500 };


	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;


	//mine
	Point2f GetInitialPosition();
	void CreateSmileys();
	void DrawSmileys() const;
	void IncreaseSpeed();
	void DecreaseSpeed();
	void UpdatePosition(float elapsed);

	void DeleteSmiley();

	void DrawBorder() const;
};