#pragma once
#include "Texture.h"
#include "utils.h"
#include <vector>
#include "Platform.h"

class Level;
class Texture;
class Blocks final : public Platform
{
public:
	explicit Blocks(Level* level,Point2f bottomLeft, int type); //constructor
	Blocks(const Blocks& other) = delete; //copy constructor
	Blocks& operator=(const Blocks& other) = delete; // assignment operator
	Blocks(Blocks&& other) = delete; // move constructor
	Blocks& operator=(Blocks&& other) = delete; // move assignment operator
	~Blocks(); //destructor

	void Draw() const; // draws all a specific block type
	float GetWidth() const;  //return blocks width
	float GetHeight() const; // returns block hieght

private:
	void SetMeasures(); //Sets block measures

	Level* m_pLevel;

	Texture* m_pBlocks; //Pointer to the texture
	std::vector<Point2f> m_BlockCollision; //holds collision points
};

