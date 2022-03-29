#pragma once
#include "utils.h"

class Camera
{
public:
	Camera(float width, float height);
	void SetLevelBounderies(const Rectf& levelBoundries);
	void Transform(const Rectf& target);
private:
	//data memebers
	float m_Width;
	float m_Height;
	Rectf m_LevelBoundaries;

	Point2f Track(const Rectf& target);
	void Clamp(Point2f& bottomLeftPos);
};

