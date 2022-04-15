#pragma once
#include "Texture.h"
#include <vector>
#include "utils.h"
#include "Platform.h"


class Cloud final : public Platform
{
public:
	explicit Cloud(Point2f bottomLeft, int nrLenght, int type, float windowWidth); //constructor
	Cloud(const Cloud& other) = delete; //copy constructor
	Cloud& operator=(const Cloud& other) = delete; // assignment operator
	Cloud(Cloud&& other) = delete; // move constructor
	Cloud& operator=(Cloud&& other) = delete; // move assignment operator
	~Cloud(); //destructor

	void Draw() const; // draws all parts of the cloud
	Vector2f GetVelocity() const; // return the cloud's velocity
	virtual float GetWidth() const;  //will never be called
	virtual float GetHeight() const; //will never be called
	//should remove this two member variables but when I do I get error messages

private:
	void SetMeasures(); //sets all the measures realated to the texture
	void SetVelocity(); //creates randomly the  clouds velocity from a range and gives direction

	void DrawLeftTexture(Point2f& bottomLeft, Rectf& sourceRect) const; //Draws Left texture and updates both the bottomLeft and the sourceRect
	void DrawCenterTexture(Point2f& bottomLeft, Rectf& sourceRect) const; //Draws Center textures and updates both the bottomLeft and the sourceRect
	void DrawRightTexture(Point2f& bottomLeft, Rectf& sourceRect) const; //Draws the right texture

	int m_MaxVelocityX; //sets the maximum absolute X Velocity
	int m_MinVelocityX; //sets the minimum absolute X Velocity
	
	Texture* m_pCloud; //hold the pointer to the cloud Texture
	static int m_InstanceCounter; // keeps track of how many clouds are there in the map
};

