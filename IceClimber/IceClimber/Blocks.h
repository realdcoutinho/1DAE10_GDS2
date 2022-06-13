#pragma once
#include "Texture.h"
#include "utils.h"
#include <vector>
#include "Platform.h"

class Stalagtites;
class Level;
class Texture;
class Player;
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
	void Update(float elapsedSec);
	float GetWidth() const;  //return blocks width
	float GetHeight() const; // returns block hieght
	void FixedBlocked();

private:
	void SetMeasures(); //Sets block measures
	void SetStalagtite(); //if it has a stalgtite it will create a stalgtite

	enum class State
	{
		fixed = 0,
		destroyed = 1,
	};
	State m_State;

	bool m_HasStalagtites;
	
	Level* m_pLevel;
	Texture* m_pBlocks; //Pointer to the texture
	Stalagtites* m_pStalagtites;

	std::vector<Point2f> m_BlockCollision; //holds collision points
};

