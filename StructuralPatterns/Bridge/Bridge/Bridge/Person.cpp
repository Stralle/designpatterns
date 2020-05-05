#include "Person.h"
#include "stdio.h"

struct Person::PersonImpl
{
	void greet(Person *p);
};

void Person::PersonImpl::greet(Person *p)
{
	printf("Hello, my name is %s.", p->name.c_str());
}

Person::Person()
	: impl(new PersonImpl)
{
}

Person::~Person()
{
	delete impl;
}

void Person::greet()
{
	impl->greet(this);
}

