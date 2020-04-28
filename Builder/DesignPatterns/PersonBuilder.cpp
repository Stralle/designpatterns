#include "PersonBuilder.h"
#include "PersonJobBuilder.h"
#include "PersonAddressBuilder.h"

inline PersonAddressBuilder PersonBuilder::lives()
{
	return PersonAddressBuilder{ person };
}

inline PersonJobBuilder PersonBuilder::works()
{
	return PersonJobBuilder{ person };
}