#pragma once
#include <vector>
#include "Person.h"

struct Person;

struct ChatRoom
{
	std::vector<Person> people;

	class PersonReference
	{
		std::vector<Person>& people;
		unsigned int index;
	public:

		PersonReference(std::vector<Person>& people, const unsigned index)
			: people(people),
			  index(index)
		{
		}

		Person* operator->() const;
		
	};

	void broadcast(const std::string& origin, const std::string& message);
	PersonReference join(Person&& p);
	void message(const std::string& origin, const std::string& who, const std::string& message);
};

