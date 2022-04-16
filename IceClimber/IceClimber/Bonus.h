#pragma once
#include "utils.h"
#include "GameObject.h"


class Texture;
class Level;
class Bonus final : public GameObject
{
public:
	explicit Bonus(Level* level, Point2f bottomLeft);
	Bonus(const Bonus& other) = delete; //copy constructor
	Bonus& operator=(const Bonus& other) = delete; // assignment operator
	Bonus(Bonus&& other) = delete; // move constructor
	Bonus& operator=(Bonus&& other) = delete; // move assignment operator
	~Bonus() override;

	void Draw() const;

private:
	void SetMeasures();
	void SetSourceRect();

	Level* m_pLevel;
	Texture* m_pTextureBonus;



	int m_NrOfBonus;
	float m_WidthTemp;
	float m_HeightTemp;


	Rectf m_SourceRect;
};

