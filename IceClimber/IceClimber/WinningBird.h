#pragma once
#include "NPC.h"
#include "Texture.h"
#include "utils.h"
class WinningBird : public NPC
{
public:
	explicit WinningBird(Point2f bottomLeft, int type);
	WinningBird(const WinningBird& other) = delete; //copy constructor
	WinningBird& operator=(const WinningBird& other) = delete; // assignment operator
	WinningBird(WinningBird&& other) = delete; // move constructor
	WinningBird& operator=(WinningBird&& other) = delete; // move assignment operator
	~WinningBird();
	void Draw() const;
private:
	void SetMeasures();

	enum class ColorBird
	{
		red = 0,
		blue = 1
	};

	int m_NrRows;
	int m_NrColumns;
	float m_TextureWidth;
	float m_TextureHeight;
	float m_TextureWidthSnipet;
	float m_TextureHeightSnipet;

	bool m_IsOverlapping;

	

	Vector2f m_Velocity;
	Rectf m_SourceRect;
	Rectf m_BirdRect;
	ColorBird m_Type;
	Texture* m_pTextureBird;
};

