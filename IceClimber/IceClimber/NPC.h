#pragma once
class NPC
{
public:
	explicit NPC(Point2f bottomLeft);
	NPC(const NPC& other) = delete; //copy constructor
	NPC& operator=(const NPC& other) = delete; // assignment operator
	NPC(NPC&& other) = delete; // move constructor
	NPC& operator=(NPC&& other) = delete; // move assignment operator
	virtual void Draw() const;

protected:
	Point2f m_BottomLeft;
};

