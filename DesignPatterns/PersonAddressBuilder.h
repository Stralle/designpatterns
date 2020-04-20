#pragma once
#include <string>
#include "PersonBuilder.h"

class PersonAddressBuilder : public PersonBuilder
{
	typedef PersonAddressBuilder Self;

public:
	explicit PersonAddressBuilder(Person& person)
		: PersonBuilder{ person }
	{
	}

	Self& at(std::string street_address)
	{
		person.street_address = street_address;
		return *this;
	}

	Self& with_postcode(std::string postal_code)
	{
		person.post_code = postal_code;
		return *this;
	}

	Self& in(std::string city)
	{
		person.city = city;
		return *this;
	}
};


