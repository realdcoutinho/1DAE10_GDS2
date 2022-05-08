// ParseSvgFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include "structs.h"

void ReadSentence(std::istream& istream, std::string& sentence);
void CheckStream(std::istream& stream);

void ReadFile(); //not in use

int main()
{
	//std::vector<Point2f> verticesLevel{};
	//std::vector<std::vector<Point2f>> svgVerticesLevel{};
	////static bool SvgLevel{ SVGParser::GetVerticesFromSvgFile("./Resources/Level.svg", svgVerticesLevel) };
	//
	//std::vector<Point2f> verticesTriangle{};
	//std::vector<std::vector<Point2f>> svgVerticesTriangle{};
	////static bool SvgTriangle{ SVGParser::GetVerticesFromSvgFile("./Resources/Level.svg", svgVerticesTriangle) };
	//
	////if (SvgLevel && SvgTriangle)
	////{
	////	verticesLevel = svgVerticesLevel[0];
	////	verticesTriangle = svgVerticesTriangle[0];
	////	std::cout << "It worked" << '\n';
	////}
	//if (SVGParser::GetVerticesFromSvgFile("./Resources/Level.svg", svgVerticesLevel))
	//{
	//	verticesLevel = svgVerticesLevel[0];
	//	//verticesTriangle = svgVerticesTriangle[0];
	//	std::cout << "It worked" << '\n';
	//}
	//else
	//{
	//	std::cout << "Level failed to load from svg" << std::endl;
	//}

	std::string text{};
	std::ifstream file{ "Resources/Level.svg" };
	CheckStream(file);
	ReadSentence(file, text);
	std::cout << text;


}

void CheckStream(std::istream& stream)
{
	std::cout << "Something went wrong while reading: ";
	if (stream.eof())
		std::cout << " End of file was reached." << '\n';
	if (stream.fail())
		std::cout << " Something failed." << '\n';
	if (stream.bad())
		std::cout << " This is really bad." << '\n';
	else
		std::cout << " I HAVE NO CLUE DUDE" << '\n';

	std::cout << '\n';
	stream.clear();
}

void ReadSentence(std::istream& istream, std::string& sentence)
{
	if (!istream)
	{
		CheckStream(istream);
		return;
	}

	std::string text;
	while (std::getline(istream, text))
	{
		if (text.size() > 0)
		{
			if (text.find('.') != std::string::npos)
			{
				text += '\n';
			}
			else
			{
				text += ' ';
			}
			sentence += text;
			text.clear();
		}
	}
}
