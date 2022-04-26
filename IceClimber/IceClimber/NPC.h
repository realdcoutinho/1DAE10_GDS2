#pragma once
#include "utils.h"
#include "Texture.h"

class NPC
{
public:
	explicit NPC(Point2f bottomLeft, float windowWidth, int nrRows, int nrColumns, int nrOfFrames,  int animFrame, float animTime, float nrOfFramesPerSec);
	NPC(const NPC& other) = delete; //copy constructor
	NPC& operator=(const NPC& other) = delete; // assignment operator
	NPC(NPC&& other) = delete; // move constructor
	NPC& operator=(NPC&& other) = delete; // move assignment operator
	virtual ~NPC();

	virtual void Draw() const;
	virtual void Update(float elapsedSed);
	bool Overlap(const Rectf& actorShape);

protected:
	void SetVelocity(float horSpeed);
	void SetMeasures(float textureWidth, float textureHeight, float textureWidthSnipet, float textureHeightSnipet, Rectf destRect);
	virtual void UpdatePosition(float elapsedSec);
	
	enum class Type
	{
		typeOne = 0,
		typeTwo = 1,
		typeThree = 2, //bird
	};

	float m_WindowWidth;

	float m_TextureWidth;
	float m_TextureHeight;
	float m_TextureWidthSnipet;
	float m_TextureHeightSnipet;

	int m_NrRows;
	int m_NrColumns;
	int m_NrOfFrames;
	int m_AnimFrame;
	float m_AnimTime;
	float m_NrOfFramesPerSec;

	bool m_IsAlive;
	bool m_IsOverlapping;

	Rectf m_ActorShape;

	Type m_Type;
	Vector2f m_Velocity;
	Point2f m_BottomLeft;
	Rectf m_DestRect;
};

