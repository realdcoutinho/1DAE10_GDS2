#pragma once
#include "utils.h"
#include "Matrix2x3.h"
#include "Texture.h"

class Diamond
{
public:
	Diamond(Point2f center);
	~Diamond();

	void DrawDiamondPoints() const;
	void DrawDiamondTexture() const;

	void Matrices(float elapsedSec);
	void PressR();

	void IsPointInDiamond(Point2f mousePos);
private:
	//Data Members
	enum class State
	{
		deselected = 0,
		selected = 1,
	};
	State m_State{0};

	Texture* m_pTextureDiamond{};

	std::vector<Point2f> m_Vertices;
	float m_RotationAngle{};
	float m_RotationSpeed{};
	float m_RotationDiretion{};
	float m_Lenght{48.f};
	float m_Scale{1};
	float m_Width{ m_Lenght };
	float m_Height{ m_Lenght };
	Vector2f m_DisplacementVector{};
	Matrix2x3 m_matWorld;
	Point2f m_centerPoint{};
	Point2f m_InitialCenterPoint{};

	//Data Functions
	void InitializeVertices();
	void InitializeTexture();
	void CalculateSpeed();

	void RotateDiamond(float elapsedSec);
	void ScaleDiamond(float elapsedSec);
	void TranslateDiamond(float elapsedSec);

	void DeleteTextures();
};

