#include <vector>
#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct Address
{
	string street;
	string city;
	int suite;

	friend ostream& operator<<(ostream& os, const Address& obj)
	{
		return os
			<< "street: " << obj.street
			<< " city: " << obj.city
			<< " suite: " << obj.suite;
	}
};

struct Contact
{
	string name;
	Address* work_address;

	Contact(const string& name, Address* work_address)
		: name{ name }, work_address{ new Address {*work_address} }
	{
	}
	
	~Contact()
	{
		delete work_address;
	}

	Contact(const Contact& other) // Deep Copy because we don't want our contacts to point to the same address.
		: name{ other.name },
		work_address(new Address{ *other.work_address })
	{
	}

	friend ostream& operator<<(ostream& os, const Contact& obj)
	{
		return os
			<< "name: " << obj.name
			<< " work_address: " << *obj.work_address;
	}

};

// Factory from which are created specified specializations of employee's prototypes based on offices.
struct EmployeeFactory
{
	static Contact main, aux;

	static unique_ptr<Contact> NewMainOfficeEmployee(string name, int suite) // Factory-way constructing a prototyped employee in a main office with specialized name and suite
	{
		return NewEmployee(name, suite, main); // Used prototype of main office employee
	}

	static unique_ptr<Contact> NewAuxOfficeEmployee(string name, int suite) // Factory-way constructing a prototyped employee in a main office with specialized name and suite
	{
		return NewEmployee(name, suite, aux); // Used prototype of aux office employee
	}
private:
	static unique_ptr<Contact> NewEmployee(string name, int suite, Contact& proto) //
	{
		auto result = make_unique<Contact>(proto);
		result->name = name;
		result->work_address->suite = suite;
		return result;
	}
};

Contact EmployeeFactory::main{ "", new Address{"123 East Dr", "London", 0} }; // Prototype for an Employee in main office.
Contact EmployeeFactory::aux{ "", new Address{"123B East Dr", "London", 0} }; // Prototype for an Employee in auxilary office.

// Rename this method to main for testing purposes
int mainPrototype()
{
	auto john = EmployeeFactory::NewMainOfficeEmployee("John", 3);
	auto jane = EmployeeFactory::NewAuxOfficeEmployee("Jane", 5);

	cout << *john << endl << *jane << endl;


	return 0;
}