#pragma once
#include "utils.h"

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

	//data member
	std::vector<Point2f> m_Vertices;
	float m_RotationAngle{};
	float m_RotationSpeed{};
	float m_RotationDiretion{};

	float m_Width{ 100.0f };
	float m_Height{ 100.0f };
	Point2f m_Center{};
	Vector2f m_DisplacementVector{};

	Rectf m_Rect{};

	void InitializeVertices();
	void DrawDiamond() const;
	void CalculateSpeed();
	void CalculateCenter();
	void RotateDiamond(float elapsedSec);
};