#pragma once
#include "utils.h"
#include <vector>
#include "GameObject.h"

class Platform : public GameObject
{
public:
	explicit Platform(Point2f bottomLeft, int nrOfRows, int nrOfColumns, int type, int nrLenght = 1, float windowWidth = 0, bool isMovable = false);
	Platform(const Platform& other) = delete; //copy constructor
	Platform& operator=(const Platform& other) = delete; // assignment operator
	Platform(Platform&& other) = delete; // move constructor
	Platform& operator=(Platform&& other) = delete; // move assignment operator
	virtual ~Platform();
	
	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity); // sets players y-position and velocity 
	bool IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity) const; // return a value in case the actor is on top of the block
	bool IsOnGround(const Rectf& actorShape) const; //returns a bool value withouting needing the velocity
	virtual float GetWidth() const = 0;  //return blocks width
	virtual float GetHeight() const = 0; // returns block hieght

	bool IsOnGroundStalgmite(const Rectf& actorShape) const;

	bool m_IsDestroyed;

protected: 
	void SetCollision(); //sets collisons from type block bottomleft onwards
	void SetLines();
	void UpdatePosition(float elapsedSec);
	virtual void SetVelocity();

	enum class Type //The type will influence later on
	{
		typeOne = 0, //start or green
		typeTwo = 1,	//middle or brown
		typeThree = 2		//end or ice
	};
	Type m_Type;


	bool m_IsMovable;

	int m_NrLenght;

	float m_WindowWidth;
	float m_TotalWidth;


	Rectf m_DestRect;
	Rectf m_SourceRect;
	Vector2f m_Velocity;
	std::vector<Point2f> m_Collision;

	std::vector<Point2f> m_TopLine;
	std::vector<Point2f> m_BottomLine;
};


