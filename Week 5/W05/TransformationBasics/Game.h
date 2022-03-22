#pragma once
#include "utils.h"
#include "Matrix2x3.h"
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
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
	// DATA MEMBERS
	const Window m_Window;

	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;

	//data member
	enum class State
	{
		deselected = 0,
		selected = 1,
	};
	State m_State{};

	Texture* m_pTextureDiamond{};

	std::vector<Point2f> m_Vertices;
	float m_RotationAngle{};
	float m_RotationSpeed{};
	float m_RotationDiretion{};
	float m_Lenght{ 48.0f };
	float m_Scale{ 1.0f };
	float m_Width{ m_Lenght };
	float m_Height{ m_Lenght };
	Vector2f m_DisplacementVector{};
	Matrix2x3 m_matWorld;
	Point2f m_centerPoint{};

	//data functions
	void InitializeVertices();
	void InitializeTexture();

	void DrawDiamondPoints() const;
	void DrawDiamondTexture() const;
	void CalculateSpeed();

	void RotateDiamond(float elapsedSec);
	void ScaleDiamond(float elapsedSec);
	void TranslateDiamond(float elapsedSec);
	void Matrices();

	void IsPointInDiamond(Point2f mousePos);

};