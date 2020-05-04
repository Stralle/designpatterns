#pragma once

#include <string>
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

class PersonBuilder;

class Person
{
	// address
	std::string street_address, post_code, city;

	//employment
	std::string company_name, position;

	int annual_income = 0;

	Person() {}

public:
	Person(Person&& other)
		: street_address(std::move(other.street_address)),
		post_code(std::move(other.post_code)),
		city(std::move(other.city)),
		company_name(std::move(other.company_name)),
		position(std::move(other.position)),
		annual_income(std::move(other.annual_income))
	{
	}

	Person& operator=(Person&& other)
	{
		if (this == &other)
			return *this;

		street_address = std::move(other.street_address);
		post_code = std::move(other.post_code);
		city = std::move(other.city);
		company_name = std::move(other.company_name);
		position = std::move(other.position);
		annual_income = other.annual_income;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Person& person)
	{
		return os
			<< "Street Address: " << person.street_address
			<< "post_code: " << person.post_code
			<< "city: " << person.city
			<< "company_name: " << person.company_name
			<< "position: " << person.position
			<< "annual_income: " << person.annual_income;
	}

	static PersonBuilder create();

	friend class PersonBuilder;
	friend class PersonAddressBuilder;
	friend class PersonJobBuilder;
};

