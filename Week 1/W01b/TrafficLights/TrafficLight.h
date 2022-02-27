#pragma once
#include "utils.h"

class TrafficLight
{
public:
	enum class State
	{
	green = 1,
	orange = 2,
	red = 3,
	off = 4,
	};
	
	explicit TrafficLight(const Point2f& pos, float width, float height);
	~TrafficLight();

	void DoHitTest(const Point2f& point);
	void Update(float elapsedSec);
	void LightChange();
	void Draw() const;

	float GetWidth() const;
	float GetHeight() const;
	int GetNrOfTrafficLights() const;

private:
	State m_State{4};
	Point2f m_Position;
	float m_AccumulatedSec{};
	float m_Radius;
	float m_Width;
	float m_Height;


	Rectf m_Armature{};
	Ellipsef m_Green{};
	Ellipsef m_Orange{};
	Ellipsef m_Red{};

	Circlef m_CircleGreen{};
	Circlef m_CircleOrange{};
	Circlef m_CircleRed{};

	Color4f m_ColorBlack{ 0, 0, 0, 1 };
	Color4f m_ColorGrey{ 0.5f, 0.5f, 0.5f, 1 };
	Color4f m_ColorGreen{ 0, 1, 0, 1 };
	Color4f m_ColorOrange{ 1, 0.4f, 0, 1 };;
	Color4f m_ColorRed{ 1, 0, 0, 1 };;

	bool IsArmatureHIt{};
	bool isGreenHit{};
	bool isOrangeHit{};
	bool isRedHit{};

	void SetState(int state);
	static int m_NumberOfTrafficLights;
};

