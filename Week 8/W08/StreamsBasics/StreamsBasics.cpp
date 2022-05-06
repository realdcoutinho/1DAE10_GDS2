// StreamsBasics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>      // std::stringstream, std::stringbuf



void ReadFile(); //not in use
void WriteFile(); // not in use
void CheckStream(std::istream& stream);
void ReadSentence(std::istream& istream, std::string& sentence);

int main()
{
    //ReadFile();
    //WriteFile();
    std::ifstream inStream{ "SoftwareQuotesInput.txt" };
    std::ofstream outStream{ "SoftwareQuotesOutput.txt" };
    std::string text;
    ReadSentence(inStream, text);
    std::cout << text;
    outStream << text;
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


void ReadFile()
{
    std::ifstream inStream{ "SoftwareQuotesInput.txt" };
    if (!inStream)
    {
        CheckStream(inStream);
        return;
    }

    std::string text;
    while (std::getline(inStream, text))
    {
        if(text.size() > 0)
        {
            if (text.find('.') != std::string::npos)
            {
                text += '\n';
            }
            else
            {
                text += ' ';
            }
            std::cout << text;
            
            text.clear();
        }
    }
}
void WriteFile()
{
    std::ifstream inStream{ "SoftwareQuotesInput.txt" };
    if (!inStream)
    {
        CheckStream(inStream);
        return;
    }

    std::ofstream outStream{ "SoftwareQuotesOutput.txt" };
    if (!outStream)
    {
        std::cout << "Something wrong";
        return;
    }

    std::string text;
    while (std::getline(inStream, text))
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
                //outStream << text;
            }
            outStream << text;

            text.clear();
        }
    }
}