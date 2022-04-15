#include "pch.h"
#include "GameObject.h"
#include <iostream>
using namespace utils;

GameObject::GameObject(Point2f bottomLeft, int nrRows, int nrColumns)
	: m_BottomLeft{ bottomLeft }
	, m_NrRows{nrRows}
	, m_NrColumns{nrColumns}
	, m_IsOverlapping{false}
	, m_TextureWidth{0} // it will be redefined later on
	, m_TextureHeight{0} // it will be redefined later on
	, m_TextureSnipetWidth{0} // it will be redefined later on
	, m_TextureSnipetHeight{0} // it will be redefined later on
	, m_SourceRect{} // it will be redefined later on
	, m_DestRect{} // it will be redefined later on
{
	std::cout << "Game Object created" << '\n';
}

GameObject::~GameObject()
{

}

void GameObject::Update(float elapsedSec)
{

}

void GameObject::Draw() const
{

}

void GameObject::Overlap(const Rectf& actorShape)
{
	if (IsOverlapping(actorShape, m_DestRect))
		m_IsOverlapping = true;
}

void GameObject::SetMeasures(float textureWidth, float textureHeight, float textureWidthSnipet, float textureHeightSnipet, Rectf destRect)
{
	m_TextureWidth = textureWidth;
	m_TextureHeight = textureHeight;
	m_TextureSnipetWidth = textureWidthSnipet;
	m_TextureSnipetHeight = textureHeightSnipet;
	m_DestRect = destRect;
}