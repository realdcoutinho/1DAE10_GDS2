#pragma once
#include "NPC.h"
#include "Texture.h"
#include "Animation.h"
#include "utils.h"

class Player;
class Level;
class WinningBird final : public NPC 
{
public:
	explicit WinningBird(Player* player, Level* level, Point2f bottomLeft, float windowWidth);
	WinningBird(const WinningBird& other) = delete; //copy constructor
	WinningBird& operator=(const WinningBird& other) = delete; // assignment operator
	WinningBird(WinningBird&& other) = delete; // move constructor
	WinningBird& operator=(WinningBird&& other) = delete; // move assignment operator
	virtual ~WinningBird() override;

	void Draw() const;
	virtual void Update(float elapsedSec) override;

private:
	void InitializeAnimation();
	void SetMeasures();
	void SetColorBird();

	enum class ColorBird
	{
		red = 0,
		blue = 1
	};

	float m_HorSpeed;
	Animation* m_AnimationBird;
	Texture* m_pTextureBird;
};

