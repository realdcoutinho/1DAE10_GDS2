#pragma once
#include "Texture.h"
#include "utils.h"
#include <vector>
#include "Platform.h"

class Blocks : public Platform
{
public:
	explicit Blocks(Point2f bottomLeft, int nrOfTypes, int type); //constructor
	Blocks(const Blocks& other) = delete; //copy constructor
	Blocks& operator=(const Blocks& other) = delete; // assignment operator
	Blocks(Blocks&& other) = delete; // move constructor
	Blocks& operator=(Blocks&& other) = delete; // move assignment operator
	~Blocks(); //destructor

	virtual void Draw() const; // draws all a specific block type
	float GetWidth() const;  //return blocks width
	float GetHeight() const; // returns block hieght

	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity); //fixes point of collision
	bool IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity) const; // return a value in case the actor is on top of the block

	enum class BlockType //The block type will influence later on
	{
		green = 0,
		brown = 1,
		blue = 2
	};
private:
	void SetMeasures(); //Sets block measures
	void SetSourceRect(); //sets source rect
	void SetCollision(); //sets collisons from type block bottomleft onwards

	int m_NrOfTypesBlocks; // number of block types	
	float m_Width; // full texture width/3 (number of types)
	float m_Height; // texture height // block hieght
	bool m_IsDestroyed; //is it destroyed?
	Rectf m_SourceRect; //source rect
	BlockType m_Type; //hold the type of block green, brown or blue
	Texture* m_pBlocks; //Pointer to the texture
	std::vector<Point2f> m_BlockCollision; //holds collision points
};

