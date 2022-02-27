#include "pch.h"
#include "DAEStudent.h"
#include <iostream>

DAEStudent::DAEStudent(const std::string& firstName,
	const std::string& lastName, Major major)
	: Person{firstName, lastName}
	, m_Major{major}
{
	std::cout << "Student constructor" << '\n';
}

DAEStudent::~DAEStudent()
{
	std::cout << "Student destructor" << '\n';
}

void DAEStudent::Identify() const
{
	std::cout << "I am a derived class DAEStudent object. My name is: " << GetName() << "\n";
}

std::string DAEStudent::GetName() const
{
	std::string name{ Person::GetName() };
	name += ", and my major is: ";
	switch (m_Major)
	{
	case DAEStudent::Major::GD:
		name += "Game Development.";
		break;
	case DAEStudent::Major::SD:
		name += "Sound Design.";
		break;
	case DAEStudent::Major::GGP:
		name += "Games Graphics Production.";
		break;
	case DAEStudent::Major::IGP:
		name += "Independent Game Production.";
		break;
	case DAEStudent::Major::ANIM:
		name += "Animation.";
		break;
	case DAEStudent::Major::VFX:
		name += "Visual Effects.";
		break;
	default:
		name += "another Major.";
		break;
	}

	//std::string major{ m_Major };
	return name;
}