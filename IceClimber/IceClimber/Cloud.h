#pragma once
#include "Texture.h"
#include <vector>
#include "utils.h"
#include "Platform.h"


class Cloud : public Platform
{
public:
	explicit Cloud(Point2f bottomLeft, int nrLenght, int type, float windowWidth); //constructor
	Cloud(const Cloud& other) = delete; //copy constructor
	Cloud& operator=(const Cloud& other) = delete; // assignment operator
	Cloud(Cloud&& other) = delete; // move constructor
	Cloud& operator=(Cloud&& other) = delete; // move assignment operator
	~Cloud(); //destructor

	void Update(float elapsedSec); // is updating both collision and position
	void Draw() const; // draws all parts of the cloud
	Vector2f GetVelocity() const; // return the cloud's velocity

	enum class CloudType //enum class for the type of cloud, either top or bottom
	{
		bottom = 0,
		top = 1,
	};

	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity); // sets players y-position and velocity 
	bool IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity) const; //return a bool value when velocity is needed
	bool IsOnGround(const Rectf& actorShape) const; //returns a bool value withouting needing the velocity

private:
	void SetMeasures(); //sets all the measures realated to the texture
	void SetSourceRect(); //sets source rect
	void SetCollision(); //pushes back the point2f into the std::vector collision
	void SetVelocity(); //creates randomly the  clouds velocity from a range and gives direction

	void DrawLeftTexture(Point2f& bottomLeft, Rectf& sourceRect) const; //Draws Left texture and updates both the bottomLeft and the sourceRect
	void DrawCenterTexture(Point2f& bottomLeft, Rectf& sourceRect) const; //Draws Center textures and updates both the bottomLeft and the sourceRect
	void DrawRightTexture(Point2f& bottomLeft, Rectf& sourceRect) const; //Draws the right texture

	void UpdateCloudPosition(float elapsedSec);

	float m_FullTextureWidth; //width of the full texture
	float m_TextureOneCloud; // width of one cloud composed by one of each part
	float m_TextureCloudSnipet; //width of each cloud segment
	float m_TextureHeight; //texture height = cloud height
	int m_NrOfTypesBlocks; //how many types of cloud are there? 2, top and bottom, they have different colors
	int m_NrLenght; // how long is the cloud? this number plus one on each sidee, so it will be nrLenght + 2
	float m_TotalCouldWidth; //Total width of the created cloud. each snipet times the nrLenght plus one of each end
	float m_WindowWidth; // hold the windowWidth

	int m_MaxVelocityX; //sets the maximum absolute X Velocity
	int m_MinVelocityX; //sets the minimum absolute X Velocity
	Vector2f m_Velocity; // holds the vector for the cloud velocity
	
	Texture* m_pCloud; //hold the pointer to the cloud Texture
	Rectf m_SourceRect; //Source rectangle to copy from the texture

	CloudType m_Type; //hold the cloud type, either top or bottom

	std::vector<Point2f> m_CloudCollision; //holds the point2f of the collsion. That is the bottomLeft and all the other points calculated by the measures set above
	static int m_InstanceCounter; // keeps track of how many clouds are there in the map
};

