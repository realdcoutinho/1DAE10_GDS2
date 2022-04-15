#pragma once
#include "Texture.h"
#include "utils.h"
#include <vector>
#include "Platform.h"

class Blocks final : public Platform
{
public:
	explicit Blocks(Point2f bottomLeft, int type, float tempWidth, float tempHeight); //constructor
	Blocks(const Blocks& other) = delete; //copy constructor
	Blocks& operator=(const Blocks& other) = delete; // assignment operator
	Blocks(Blocks&& other) = delete; // move constructor
	Blocks& operator=(Blocks&& other) = delete; // move assignment operator
	~Blocks(); //destructor

	void Draw(Texture* textureOne) const; // draws all a specific block type
	float GetWidth() const;  //return blocks width
	float GetHeight() const; // returns block hieght

private:
	void SetMeasures(); //Sets block measures

	float m_TextureWidthTemp;
	float m_TextureHeightTemp;

	Texture* m_pBlocks; //Pointer to the texture
	std::vector<Point2f> m_BlockCollision; //holds collision points
};

