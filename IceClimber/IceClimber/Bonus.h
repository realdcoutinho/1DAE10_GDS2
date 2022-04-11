#pragma once
#include "Texture.h"
#include "utils.h"
class Bonus
{
public:
	Bonus(Point2f bottomLeft);
	Bonus(const Bonus& other) = delete; //copy constructor
	Bonus& operator=(const Bonus& other) = delete; // assignment operator
	Bonus(Bonus&& other) = delete; // move constructor
	Bonus& operator=(Bonus&& other) = delete; // move assignment operator
	~Bonus();

	void Draw() const;
	void Overlap(const Rectf& actorShape);

private:
	void SetMeasures();
	int GetRandomBonus();
	void SetDestRect();
	void SetSourceRect();

	bool m_IsCaught;
	int m_NrOfBonus;
	float m_TextureWidth;
	float m_TextureHeight;
	float m_TextureSnipetWidth;

	Point2f m_BottomLeft;
	Texture* m_pTextureBonus;
	Rectf m_SourceRect;
	Rectf m_DestRect;
};

