#pragma once
#include "utils.h"
#include "Texture.h"

class Level;
class Avatar
{
public:
	enum class ActionState
	{
		waiting = 0,
		moving = 1,
		transforming = 2
	};

	Avatar();
	~Avatar();
	void Update(float elapsedSec, const Level* level);
	void Draw();
	void PowerUpHit();
	Rectf GetShape();

private:
	
	float m_HorSpeed{ 200.0f };
	float m_JumpSpeed{ 600.0f };
	Vector2f m_Velocity{ 0.0f, 0.0f };
	Vector2f m_Acceleration{ 0.0f, -981.0f };
	ActionState m_ActionState = ActionState::moving;
	float m_AccuTransformSec{ 0.0f };
	float m_MaxTransformSec{ 1.0f };
	int m_Power{ 0 };

	void Move(float elapsedSec);
	void Transform(float elapsedSec);
	void UpdateState(float elapsedSec, const Level* pLevel);
	void DrawRectAvatar() const;

	Texture* m_pSpritesTexture;
	float m_ClipHeight{ 97.0f };
	float m_ClipWidth{ 72.0f };
	int m_NrOfFrames{ 10 };
	int m_NrOfFramesPerSec{10};
	float m_AnimTime{};
	int m_AnimFrame{};

	Rectf m_Dest;

	Rectf m_Shape{ 50, 280, m_ClipWidth, m_ClipHeight };

	void DrawAvatarTexture();
	void UpdateFrames(float elapsedSec);






};

