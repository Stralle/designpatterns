#pragma once
#include <string>

struct Person
{
	std::string name;

	struct PersonImpl;
	PersonImpl* impl;

	Person();
	~Person();

	void greet();

};

