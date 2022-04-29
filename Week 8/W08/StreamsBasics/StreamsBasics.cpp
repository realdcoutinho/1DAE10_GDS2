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
    //std::cout << "Hello World!\n";
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
    std::ifstream inStream{ "SoftwareQuotesInput.txt" };
    if (!inStream)
        CheckStream(inStream);

    std::string text;
    std::string total;
    while (std::getline(inStream, text, '\n'))
    {
        std::cout << text << ' ';
        if(std::getline(inStream, text, '\n'))
        {
            std::cout << text << '\n';
            if (std::getline(inStream, text, '.'))
            {
                std::cout << text << '\n';
            }
        }
    }
}