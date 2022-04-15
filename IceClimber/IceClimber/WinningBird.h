#pragma once
#include "NPC.h"
#include "Texture.h"
#include "utils.h"
class WinningBird final : public NPC 
{
public:
	explicit WinningBird(Point2f bottomLeft, float windowWidth);
	WinningBird(const WinningBird& other) = delete; //copy constructor
	WinningBird& operator=(const WinningBird& other) = delete; // assignment operator
	WinningBird(WinningBird&& other) = delete; // move constructor
	WinningBird& operator=(WinningBird&& other) = delete; // move assignment operator
	virtual ~WinningBird() override;

	void Draw(Texture* textureOne) const;
	virtual void Update(float elapsedSec) override;

private:
	void SetMeasures();
	void SetColorBird();

	enum class ColorBird
	{
		red = 0,
		blue = 1
	};

	float m_HorSpeed;
	Texture* m_pTextureBird;
};

