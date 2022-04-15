#pragma once
#include "Texture.h"
#include "utils.h"
#include "GameObject.h"

class Bonus final : public GameObject
{
public:
	explicit Bonus(Point2f bottomLeft, float width, float height);
	Bonus(const Bonus& other) = delete; //copy constructor
	Bonus& operator=(const Bonus& other) = delete; // assignment operator
	Bonus(Bonus&& other) = delete; // move constructor
	Bonus& operator=(Bonus&& other) = delete; // move assignment operator
	~Bonus() override;

	void Draw(Texture* textureOne) const;

private:
	void SetMeasures();
	void SetSourceRect();

	int m_NrOfBonus;
	float m_WidthTemp;
	float m_HeightTemp;

	//Texture* m_pTextureBonus;
	Rectf m_SourceRect;
};

