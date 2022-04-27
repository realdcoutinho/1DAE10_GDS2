// Theory_Streams.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>



void ReadFile();
void WriteFile();
void CheckStream(std::ifstream& stream);

int main()
{
    std::cout << "Hello World!\n";
    ReadFile();
    WriteFile();
}

void  ReadFile()
{
    {
        std::ifstream inStream{ "test.txt" };
        if (!inStream)
            std::cout << "File not opened.\n";

        int posX{}, posY{}, width{}, height{};
        std::string text;

        inStream >> text >> posX >> posY;

        if (!inStream)
            CheckStream(inStream);
        std::cout << text << ' ' << posX << ' ' << posY << '\n';


        inStream >> text >> posX >> posY; // if the stream is in an error state, we have to clear the flags before reading smt and moving on. this was an example
        if (!inStream)
            CheckStream(inStream);
        std::cout << text << ' ' << posX << ' ' << posY << '\n';


        //inStream >> text >> width;
        //if (!inStream)
        //    CheckStream(inStream);
        //std::cout << text << ' ' << width << '\n';


        inStream >> text >> height;
        if (!inStream)
            CheckStream(inStream);
        std::cout << text << ' ' << height << '\n';

        inStream.get();
        std::getline(inStream, text);
        if (!inStream)
            CheckStream(inStream);
        std::cout << text << '\n';

        while (inStream) {
            std::getline(inStream, text, 'a');
            std::cout << text << '\n';
        }
    }




    {
        std::cout << '\n' << '\n' << '\n';
        std::string text;
        std::ifstream inStream{ "test.txt" };
        while (std::getline(inStream, text))
        {
            std::cout << text << '\n';
        }
    }
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

void WriteFile()
{
    std::ofstream outStream{ "output.txt" };
    outStream << "Hello world! \n";
    outStream << "He said: 'Hi' \n";
    outStream << R"(He said: "Hi!")" << '\n';
}