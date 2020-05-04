#pragma once
#include <string>
#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

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

