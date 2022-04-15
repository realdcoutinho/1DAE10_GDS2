#pragma once
#include "utils.h"
class GameObject
{
public:
	GameObject(Point2f bottomLeft, int nrRows, int nrColumns);
	GameObject(const GameObject& other) = delete; //copy constructor
	GameObject& operator=(const GameObject& other) = delete; // assignment operator
	GameObject(GameObject&& other) = delete; // move constructor
	GameObject& operator=(GameObject&& other) = delete; // move assignment operator
	virtual ~GameObject();


	//virtual void Draw() const = 0;
	virtual void Draw() const ;
	//void Draw(Texture* textureOne) const;
	virtual void Update(float elapsedSec);
	void Overlap(const Rectf& actorShape);

protected:
	void SetMeasures(float textureWidth, float textureHeight, float textureWidthSnipet, float textureHeightSnipet, Rectf destRect);

	int m_NrRows;
	int m_NrColumns;

	bool m_IsOverlapping;
	//float m_WindowWidth;
	float m_TextureWidth;
	float m_TextureHeight;
	float m_TextureSnipetWidth;
	float m_TextureSnipetHeight;

	Point2f m_BottomLeft;
	Rectf m_SourceRect;
	Rectf m_DestRect;
};

