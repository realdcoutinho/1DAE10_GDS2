// The query type (const) methods are not indicated as such, 
// but we expect you to indicate these using const.
#include "pch.h"
#include "utils.h"
// -- Smiley.h file --
#pragma once
class  Texture; // class forward declaration
class Smiley
{
public:

	enum class State
	{
		happy = 0,
		neutral = 1,
		angry = 2,
		sleepy= 3
	};

	Smiley( const Point2f& position);
	~Smiley( );

	void Draw( );
	void Update( float elapsedSec, const Rectf& boundingRect, const Rectf& safeRect );
	void HitTest( const Point2f& pos );
	bool IsSleeping( );
	Point2f GetPosition( );
	void SetHighest( bool isHighest );
	void IncreaseSpeed( );
	void DecreaseSpeed( );

	float GetWidth() const;
	float GetHeight() const;

private:
	// DATA MEMBERS
	static Texture* m_pSmileyTexture;
	static int m_InstanceCounter;

	Point2f m_Position;
	Vector2f m_Velocity;
	Vector2f m_CurrentVelocity;
	Vector2f m_VelocityZero;
	bool m_IsHighest;
	bool m_IsSleeping{false};
	bool m_IsInSafeArea{};


	//mine
	float m_TextureWidth;
	float m_TextureHeight;
	int m_State{};


	// FUNCTIONS
	bool IsInSafeArea( const Rectf& safeRect );

	//mine
	void DeleteSmileys();
	void CreateTextures();
	void BoundingEdges(const Rectf& boundingRect, float elapsedSec);
	void SetVelocity();
	void SetState(const Rectf& safeRect);
};



