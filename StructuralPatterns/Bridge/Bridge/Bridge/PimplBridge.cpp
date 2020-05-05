/*
	Bridge - A mechanism that decouples an interface (hierarchy) from an implementation (hierarchy).

	Pimpl idiom - pointer to implementation.
	Technique that removes implementation details of a class from its object representation by placing them in a separate class accessed through an opauqe pointer.
*/

#include "Person.h"

// PIMPL example main. Rename this method to main to test this out.
int PIMPLmain()
{
	Person p;
	p.name = "Pera";
	p.greet();

	return 0;
}