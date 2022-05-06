#include "pch.h"
#include "Game.h"
#include "DaeShape.h"
#include "DaeEllipse.h"
#include "DaeRectangle.h"
#include "DaeCircle.h"
#include "DaeRectLabel.h"
#include "Vector2f.h"
#include <iostream>
#include <sstream>
#include <cassert>


#include <string>
#include <sstream>      // std::stringstream, std::stringbuf

#include <fstream>

Game::Game(const Window& window)
	:m_Window{ window }
{
	Initialize();
	if (!m_ShapesTxt)
	{
		CheckStream(m_ShapesTxt);
		return;
	}
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	BasicTesting();
	CreateLabelFont();
	CreateShapesFromFile("Resources/Shapes.txt");
}

void Game::Cleanup()
{
	SaveShapesToFile("Resources/SavedShapes.txt");
	DeleteShapes();
	CloseLabelFont();
}

void Game::Update(float elapsedSec)
{
	MoveShapes(elapsedSec);
}

void Game::Draw() const
{
	ClearBackground();
	DrawShapes();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::CreateLabelFont()
{
	m_pFont = TTF_OpenFont("./Resources/DIN-Light.otf", 16);
	if (m_pFont == nullptr)
	{
		std::cerr << "Game::CreateFont, error when calling TTF_OpenFont: " << TTF_GetError() << std::endl;
	}
}

void Game::CloseLabelFont()
{
	if (m_pFont != nullptr)
	{
		TTF_CloseFont(m_pFont);
		m_pFont = nullptr;
	}
}

void Game::DeleteShapes()
{
	for (DaeShape* pShape : m_pShapes)
	{
		delete pShape;
	}
	m_pShapes.clear();
}

void Game::DrawShapes() const
{
	for (DaeShape* pShape : m_pShapes)
	{
		pShape->Draw();
	}
}

void Game::MoveShapes(float elapsedSec)
{
	Vector2f transVec{};

	// Check keyboard
	const Uint8 *pKeyStates = SDL_GetKeyboardState(nullptr);
	if (pKeyStates[SDL_SCANCODE_RIGHT])
	{
		transVec.x += m_TransPerSec * elapsedSec;
	}
	if (pKeyStates[SDL_SCANCODE_LEFT])
	{
		transVec.x -= m_TransPerSec * elapsedSec;
	}
	if (pKeyStates[SDL_SCANCODE_DOWN])
	{
		transVec.y -= m_TransPerSec * elapsedSec;
	}
	if (pKeyStates[SDL_SCANCODE_UP])
	{
		transVec.y += m_TransPerSec * elapsedSec;
	}

	// Move shapes
	for (DaeShape* pShape : m_pShapes)
	{
		pShape->Translate(transVec);
	}
}

Color4f Game::ToColor(const std::string& colorStr) const
{
	// TODO: 1a. Complete the ToColor function definition
	// The parameter contains a color in the format: "r,g,b,a"

	// This function converts this color into a Color4f type and returns it

	Color4f color;

	std::stringstream stringOne{ colorStr };
	std::string text;

	
	std::getline(stringOne, text, ',');
	color.r = std::stof(text);
	std::getline(stringOne, text, ',');
	color.g = std::stof(text);
	std::getline(stringOne, text, ',');
	color.b = std::stof(text);
	std::getline(stringOne, text, ',');
	color.a = std::stof(text);

	//while (std::getline(stringOne, text, ','))
	//{
	//	switch (position)
	//	{
	//	case(static_cast<int>(Colors::red)):
	//		color.r = std::stof(text);
	//		break;
	//	case(static_cast<int>(Colors::green)):
	//		color.g = std::stof(text);
	//		break;
	//	case(static_cast<int>(Colors::blue)):
	//		color.b = std::stof(text);
	//		break;
	//	case(static_cast<int>(Colors::alpha)):
	//		color.a = std::stof(text);
	//		break;
	//	}
	//	++position;
	//}
	return color;
}

bool Game::ToBool(const std::string& boolStr) const
{
	// TODO: 2a. Complete the ToBool function definition
	// The parameter contains a bool in text form: "true" or "false"
	// This function converts this information into a bool type and returns it
	// This function converts this information into a bool type and returns it
	if (boolStr == "true" || boolStr == "TRUE") return true;
	else if (boolStr == "false" || boolStr == "FALSE") return false;
	return false;
}

Point2f Game::ToPoint2f(const std::string& point2fStr) const
{
	// TODO: 3a. Complete the ToPoint2f function definition
	// The parameter contains a point in the format: "x,y"
	// This function converts this information into a Point2f type and returns it
	Point2f point;

	enum class Coordinate
	{
		x = 0,
		y = 1
	};

	std::stringstream stringOne{ point2fStr };
	std::string text;

	int position{};
	while (std::getline(stringOne, text, ','))
	{
		switch (position)
		{
		case(static_cast<int>(Coordinate::x)):
			point.x = std::stof(text);
			break;
		case(static_cast<int>(Coordinate::y)):
			point.y = std::stof(text);
			break;
		}
		++position;
	}
	return point;
}

std::string Game::GetAttributeValue(const std::string& attrName, const std::string& element) const
{
	// TODO: 4a. Complete GetAttributeValue function
	// It looks for the value of the given attribute (attrName) 
	// in the given element and returns it
	std::string attribute;

		size_t start{ element.find(attrName, 0) };
		size_t firstQuote{ element.find('"', start + attrName.length()) };
		size_t secondQuote{ element.find('"', firstQuote + 1) };
		size_t subLenght{ secondQuote - firstQuote - 1 };
		attribute = element.substr(firstQuote + 1, subLenght);

	return attribute;
}

void Game::CreateShapesFromFile(const std::string& fileName)
{
	// TODO: 5. Read the XML shape elements from the given file
	// Call for each read DAE shape element the function CreateShape 

	std::ifstream file{ fileName };

	std::string shape{};
	std::string text{};
	std::string keyWord{ "Dae" };


	while (std::getline(file, text))
	{
		size_t firstPos{ text.find(keyWord, 0) };
		size_t secondPos{ text.find("\n", firstPos) };
		size_t subLenght{ secondPos - firstPos - 1 };
		shape = fileName.substr(firstPos, subLenght);
		CreateShape(shape);
	}


}

void Game::SaveShapesToFile(const std::string & fileName) const
{
	// TODO: 6. Complete the definition of SaveShapesToFile
	// Save all the shapes that are in the vector m_pShapes to the given file
	// in  the same XML format

}

void Game::CreateShape(const std::string& shapeElement)
{
	if (shapeElement.find("DaeRectangle") != std::string::npos)
	{
		CreateRectangle(shapeElement);
	}
	else if (shapeElement.find("DaeEllipse") != std::string::npos)
	{
		CreateEllipse(shapeElement);
	}
	else if (shapeElement.find("DaeRectLabel") != std::string::npos)
	{
		CreateRectLabel(shapeElement);
	}
}

void Game::CreateRectangle(const std::string& rectangleElement)
{
	Point2f center = ToPoint2f(GetAttributeValue("Center", rectangleElement));
	float width = std::strtof(GetAttributeValue("Width", rectangleElement).data(), nullptr);
	float height = std::strtof(GetAttributeValue("Height", rectangleElement).data(), nullptr);
	Color4f color = ToColor(GetAttributeValue("Color", rectangleElement));

	m_pShapes.push_back(new DaeRectangle(center, width, height, color));
}

void Game::CreateRectLabel(const std::string& rectLabelElement)
{
	Point2f center = ToPoint2f(GetAttributeValue("Center", rectLabelElement));
	float width = std::strtof(GetAttributeValue("Width", rectLabelElement).data(), nullptr);
	float height = std::strtof(GetAttributeValue("Height", rectLabelElement).data(), nullptr);
	Color4f color = ToColor(GetAttributeValue("Color", rectLabelElement));
	std::string label = GetAttributeValue("Label", rectLabelElement);
	Color4f textColor = ToColor(GetAttributeValue("TextColor", rectLabelElement));
	std::string textColorStr = GetAttributeValue("TextColor", rectLabelElement);

	m_pShapes.push_back(new DaeRectLabel(center, width, height, color, label, textColor, m_pFont));
}

void Game::CreateEllipse(const std::string& ellipseElement)
{
	Point2f center = ToPoint2f(GetAttributeValue("Center", ellipseElement));
	float width = std::strtof(GetAttributeValue("Width", ellipseElement).data(), nullptr);
	float height = std::strtof(GetAttributeValue("Height", ellipseElement).data(), nullptr);
	Color4f color = ToColor(GetAttributeValue("Color", ellipseElement));
	bool isFilled = ToBool(GetAttributeValue("IsFilled", ellipseElement));

	m_pShapes.push_back(new DaeEllipse(center, width, height, color, isFilled));
}

#pragma region Tests
void Game::BasicTesting() const
{
	// TODO: 1b. Uncomment this call of TestToColor
	TestToColor();

	// TODO: 2b. Uncomment this call of TestToBool
	TestToBool();

	// TODO: 3b. Uncomment this call of TestToPoint2f
	TestToPoint2f();

	// TODO: 4b. Uncomment this call of TestGetAttributeValue
	TestGetAttributeValue();
}

void Game::TestToColor() const
{
	std::cout << "--> ToColor function test ";
	// Create a color in string format
	Color4f inputColor{ 0.5f, 0.1f, 0.3f, 0.6f };
	std::stringstream colorStream;
	colorStream << inputColor.r << "," << inputColor.g << "," << inputColor.b << "," << inputColor.a;

	// Call the function under test
	Color4f resultColor = ToColor(colorStream.str());

	//// Verify the result of the function call
	const float smallValue{ 0.00001f };
	assert(abs(inputColor.r - resultColor.r) < smallValue);
	assert(abs(inputColor.g - resultColor.g) < smallValue);
	assert(abs(inputColor.b - resultColor.b) < smallValue);
	assert(abs(inputColor.a - resultColor.a) < smallValue);

	std::cout << " succeeded\n";
}

void Game::TestToBool() const
{
	std::cout << "--> ToBool function test ";
	assert(ToBool("false") == false);
	assert(ToBool("true") == true);

	std::cout << " succeeded\n";
}

void Game::TestToPoint2f() const
{
	std::cout << "--> ToPoint2f function test ";
	// Create a Point2f in string format
	Point2f inputPoint2f{ 3.21f,-4.56f };
	std::stringstream point2fStream;
	point2fStream << inputPoint2f.x << "," << inputPoint2f.y;

	// Call the function under test
	Point2f resultPoint2f = ToPoint2f(point2fStream.str());

	// Verify the result of the function call
	const float smallValue{ 0.00001f };
	assert(abs(inputPoint2f.x - resultPoint2f.x) < smallValue);
	assert(abs(inputPoint2f.y - resultPoint2f.y) < smallValue);

	std::cout << " succeeded\n";
}

void Game::TestGetAttributeValue() const
{
	std::cout << "--> GetAttributeValue function test ";
	// Create an attribute value
	std::string element{ R"(<DaeEllipse \nCenter="20,40" \nWidth="30" \nHeight="40" \nColor="1.0,0.6,0.07,1.0" \nIsFilled="true"/>)" };

	// Call the function under test and verify the result
	std::string result{ GetAttributeValue("Center", element) };
	assert(result == "20,40");

	result = GetAttributeValue("Width", element);
	assert(result == "30");

	result = GetAttributeValue("Height", element);
	assert(result == "40");

	result = GetAttributeValue("Color", element);
	assert(result == "1.0,0.6,0.07,1.0");

	result = GetAttributeValue("IsFilled", element);
	assert(result == "true");

	std::cout << " succeeded\n";
}

void Game::CheckStream(std::istream& stream)
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

#pragma endregion Tests
