#include "pch.h"
#include <iostream>
#include "Animation.h"
#include "Level.h"
#include "Game.h"
using namespace utils;

Animation::Animation(Texture* texture, int animationType, int animFrame, int nrOfFrames, float nrFramesPerSec, float nrColumns, float nrRows, bool loopOnce)
	: m_pTexture{texture}
	, m_AnitmationType{animationType}
	, m_AnimFrame{ animFrame }
	, m_NrOfFrames{ nrOfFrames }
	, m_NrOfFramesPerSec{ nrFramesPerSec }
	, m_NrOfColumns{ nrColumns }
	, m_AnimTime{0}
	, m_NrOfRows{ nrRows }
	, m_LoopOnce{ loopOnce }
{
	SetMeasures();
	std::cout << "ANIMATION WAS CREATED" << '\n';
}

//Animation::Animation(Level* level, std::string& string, int animationType, int animFrame, int nrOfFrames, float nrFramesPerSec, float nrColumns, float nrRows)
//	: Animation{ string, animationType, animFrame, nrOfFrames, nrFramesPerSec, nrColumns, nrRows}
//{
//	m_pTexture = level->GetTextureManager()->GetTexturePointer(string);
//}

//Animation::Animation(Game* game, std::string& string, int animationType, int animFrame, int nrOfFrames, float nrFramesPerSec, float nrColumns, float nrRows)
//	: Animation{ string, animationType, animFrame, nrOfFrames, nrFramesPerSec, nrColumns, nrRows }
//{
//	m_pTexture = game->GetTextureManager()->GetTexturePointer(string);
//}

Animation::~Animation()
{

}

void Animation::Update(float elapsedSec)
{
	const float maxFrameTime{ 1.0f / m_NrOfFramesPerSec };
	m_AnimTime += elapsedSec;
	if (maxFrameTime < m_AnimTime)
	{
		m_AnimFrame = (m_AnimFrame + 1) % m_NrOfFrames;
		m_AnimTime -= maxFrameTime;
	}
}

void Animation::Draw(Point2f bottomLeft)
{
	m_pTexture->Draw(bottomLeft, GetSourceRect());
}


Rectf Animation::GetSourceRect() const
{
	return Rectf{ m_ClipWidth * m_AnimFrame, m_ClipHeight * -(m_AnitmationType), m_ClipWidth, m_ClipHeight};
}

void Animation::SetMeasures()
{
	m_WidthTexture = m_pTexture->GetWidth();
	m_HeightTexture = m_pTexture->GetHeight();
	m_ClipWidth = m_WidthTexture / m_NrOfColumns;
	m_ClipHeight = m_HeightTexture / m_NrOfRows;
}

