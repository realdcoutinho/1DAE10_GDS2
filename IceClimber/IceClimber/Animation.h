#pragma once
#include "utils.h"
#include "Texture.h"

class Level;
class Game;
class Animation
{
public:
	Animation(Texture* texture, int animationType, int animFrame, int nrOfFrames, float nrFramesPerSec, float nrColumns, float nrRows, bool loopOnce = false);
	Animation(const Animation& other) = delete; //copy constructor
	Animation& operator=(const Animation& other) = delete; // assignment operator
	Animation(Animation&& other) = delete; // move constructor
	Animation& operator=(Animation&& other) = delete; // move assignment operator
	~Animation();

	void Update(float elapsedSec);
	void Draw(Point2f bottomLeft = Point2f{0,0});

private:

	void SetMeasures();
	Rectf GetSourceRect() const;


	Texture* m_pTexture;

	bool m_LoopOnce;
	bool m_IsCalled;

	float m_NrOfFramesPerSec;
	float m_NrOfColumns;
	float m_AnimTime{};
	float m_NrOfRows;
	float m_WidthTexture;
	float m_HeightTexture;
	float m_ClipWidth;
	float m_ClipHeight;

	int m_AnitmationType; 
	int m_AnimFrame;
	int m_NrOfFrames;


};

