// StreamsBasics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>      // std::stringstream, std::stringbuf



void ReadFile();
void CheckStream(std::ifstream& stream);

int main()
{
    ReadFile();
}

void CheckStream(std::ifstream& stream)
{
    std::cout << "Something went wrong while reading: ";
    if (stream.eof())
        std::cout << " End of file was reached." << '\n';
    if (stream.fail())
        std::cout << " Something failed." << '\n';
    if (stream.bad())
        std::cout << " This is really bad." << '\n';

    std::cout << '\n';
    stream.clear();
}

void ReadFile()
{
    std::ifstream quotes{ "SoftwareQuotesInput.txt" };
    if (!quotes)
        CheckStream(quotes);

    std::string textOne;
    std::string textTwo;
    std::string textThree;


    while (std::getline(quotes, textOne, '\n'))
    {
        std::cout << textOne << '\n';
    }

}