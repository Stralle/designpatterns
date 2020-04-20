#pragma once
#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;
class Person;

class PersonBuilder
{
	Person p;

protected:
	Person& person;

	explicit PersonBuilder(Person& person)
		: person{ person }
	{
	}

public:
	PersonBuilder() : person{ p } {}

	operator Person()
	{
		return std::move(person);
	}

	PersonAddressBuilder lives();
	PersonJobBuilder works();

};

