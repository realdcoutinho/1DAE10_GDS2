#include "pch.h"
#include <iostream>
#include "TrafficLight.h"
using namespace utils;

int TrafficLight::m_NumberOfTrafficLights{ 0 };

TrafficLight::TrafficLight(const Point2f& pos, float width, float height)
	: m_Position(pos)
	, m_Width{ width }
	, m_Height{ height }
	, m_Radius{ 30 }
	, m_Armature{ pos.x, pos.y, m_Width, m_Height }
	, m_Green {pos.x + (m_Armature.width/2), pos.y + (m_Armature.height/5), m_Radius, m_Radius }
	, m_CircleGreen { pos.x + (m_Armature.width / 2), pos.y + (m_Armature.height / 5), m_Radius }
	, m_Orange { pos.x + (m_Armature.width / 2), pos.y + (m_Armature.height / 2), m_Radius, m_Radius }
	, m_CircleOrange{ pos.x + (m_Armature.width / 2), pos.y + (m_Armature.height / 2), m_Radius }
	, m_Red{ pos.x + (m_Armature.width / 2), pos.y + (m_Armature.height /5) * 4, m_Radius, m_Radius }
	, m_CircleRed{ pos.x + (m_Armature.width / 2), pos.y + (m_Armature.height / 5) * 4, m_Radius }
{
	++m_NumberOfTrafficLights;
	std::cout << "Traffic Light generated number: " << m_NumberOfTrafficLights << " was generated!";
	std::cout << '\n';
}

TrafficLight::~TrafficLight()
{
	std::cout << ": destructor is executed! Light Number: " << m_NumberOfTrafficLights << " wasd destroyed!";
	std::cout << '\n';
	--m_NumberOfTrafficLights;
}

void TrafficLight::DoHitTest(const Point2f& point)
{
	bool IsArmatureHIt	= IsPointInRect(point, m_Armature) ;
	bool isGreenHit		= IsPointInCircle(point, m_CircleGreen);
	bool isOrangeHit	= IsPointInCircle(point, m_CircleOrange);
	bool isRedHit		= IsPointInCircle(point, m_CircleRed);

	if (IsArmatureHIt && !(isGreenHit) && !(isOrangeHit) && !(isRedHit)) {
		std::cout << "Armature is hit" << '\n';
		SetState(4);
	}
	if (isGreenHit) {
		std::cout << "Green is hit" << '\n';
		SetState(1);
	}
	if (isOrangeHit) {
		std::cout << "Orange is hit" << '\n';
		SetState(2);
	}
	if (isRedHit) {
		std::cout << "Red is hit" << '\n';
		SetState(3);
	}
}

void TrafficLight::Update(float elapsedSec)
{
	m_AccumulatedSec += elapsedSec;
}

void TrafficLight::Draw()
{
	SetColor(m_ColorBlack);
	FillRect(m_Armature);

	switch (m_State)
	{
	case State(1):
		SetColor(m_ColorGreen);
		FillEllipse(m_Green);
		SetColor(m_ColorGrey);
		FillEllipse(m_Orange);
		FillEllipse(m_Red);
		break;
	case State(2):
		SetColor(m_ColorOrange);
		FillEllipse(m_Orange);
		SetColor(m_ColorGrey);
		FillEllipse(m_Green);
		FillEllipse(m_Red);
		break;
	case State(3):
		SetColor(m_ColorRed);
		FillEllipse(m_Red);
		SetColor(m_ColorGrey);
		FillEllipse(m_Green);
		FillEllipse(m_Orange);
		break;
	case State(4):
		SetColor(m_ColorGrey);
		FillEllipse(m_Green);
		FillEllipse(m_Orange);
		FillEllipse(m_Red);
		break;
	}
}

float TrafficLight::GetWidth() const
{
	return m_Armature.width;
}

float TrafficLight::GetHeight() const
{
	return m_Armature.height;
}

void TrafficLight::SetState(int state)
{
	m_State = State(state);
}

void TrafficLight::LightChange()
{
	switch (m_State)
	{
	case State(1): //green
		if (m_AccumulatedSec >= 4) {
			m_AccumulatedSec = 0;
			m_State = State(2); // to orange
		}
		break;
	case State(2): //orange
		if (m_AccumulatedSec >= 1) {
			m_AccumulatedSec = 0;
			m_State = State(3); // to red
		}
		break;
	case State(3): //red
		if (m_AccumulatedSec >= 4) {
			m_AccumulatedSec = 0;
			m_State = State(1); // to green
		}
		break;
	case State(4):
		m_AccumulatedSec = 0;
		break;
	}
}

int TrafficLight::GetNrOfTrafficLights() const
{
	return m_NumberOfTrafficLights;
}
