#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

int main()
{
	Person p = Person::create()
		.lives().at("123 London Road").with_postcode("SW1 1GB").in("London")
		.works().at("PragmaSoft").as_a("Consultant").earning(10e6);

	cout << p << endl;

	return 0;
}