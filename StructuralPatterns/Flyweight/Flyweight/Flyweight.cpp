/*
	Flyweight is a pattern/space optimization technique that lets us use less memory by storing externally the data associated with similar objects.
*/

#include <iostream>
#include <string>
#include <ostream>

using namespace std;

#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>

using namespace boost;

typedef uint32_t key;

struct User
{
	User(const string& first_name, const string& last_name)
		: first_name(add(first_name)),
		  last_name(add(last_name))
	{
	}

	const string& get_first_name() const
	{
		return names.left.find(first_name)->second;
	}

	const string& get_last_name() const
	{
		return names.left.find(last_name)->second;
	}

	friend std::ostream& operator<<(std::ostream& os, const User& obj)
	{
		return os
			<< "First name: " << obj.first_name << " " << obj.get_first_name()
			<< " Last name: " << obj.last_name << " " << obj.get_last_name();

	}
	
protected:
	static bimap<key, string> names;
	static int seed;
	
	static key add(const string& s)
	{
		auto it = names.right.find(s);
		if (it == names.right.end())
		{
			key id = ++seed;
			names.insert(bimap<key, string>::value_type(seed, s));
			return id;
		}
		return it->second;
	}

	key first_name, last_name;
};

int User::seed = 0;
bimap<key, string> User::names{};

struct User2
{
	flyweight<string> first_name, last_name;

	User2(const string& first_name, const string& last_name)
		: first_name(first_name),
		  last_name(last_name)
	{
	}

	friend ostream& operator<<(ostream& os, const User2& obj)
	{
		return os
			<< "First name: " << obj.first_name
			<< "Last name: " << obj.last_name;
	}
};

int main(int ac, char* av)
{
	
	// Home-Made Flyweight
	/*
	const User john_doe{ "John", "Doe" };
	const User jane_doe{ "Jane", "Doe" };

	cout << "John: " << john_doe << endl;
	cout << "Jane: " << jane_doe << endl;
	*/

	// Boost.Flyweight example
	const User2 john_doe{ "John", "Doe" };
	const User2 jane_doe{ "Jane", "Doe" };

	cout << "John: " << john_doe << endl;
	cout << "Jane: " << jane_doe << endl;

	cout << std::boolalpha << (&jane_doe.last_name.get() == &john_doe.last_name.get()) << endl; // Both last name point to the same memory reference.
	
	return 0;
}