#include "pch.h"
#include "NPC.h"
#include <iostream>

NPC::NPC(Point2f bottomLeft)
	: m_BottomLeft{ bottomLeft }
{
	std::cout << "NPC was created" << '\n';
}

void NPC::Draw() const
{

}